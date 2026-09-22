import unittest
from unittest.mock import MagicMock, patch
import sys
import os
import sqlite3
import json

# Ensure services/musashi_ii directory is on sys.path for direct and root test runs
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

# Dynamic fallback mock for serial module if pyserial is not installed in environment
try:
    import serial
    import serial.tools.list_ports
except ImportError:
    mock_serial = MagicMock()
    mock_serial.EIGHTBITS = 8
    mock_serial.PARITY_NONE = 'N'
    mock_serial.STOPBITS_ONE = 1
    mock_serial.SerialException = type('SerialException', (Exception,), {})
    sys.modules['serial'] = mock_serial
    sys.modules['serial.tools'] = MagicMock()
    sys.modules['serial.tools.list_ports'] = MagicMock()
    import serial
    import serial.tools.list_ports

from read_musashi import (
    MusashiDispenser,
    MockMusashiDispenser,
    resolve_serial_port,
    load_config,
    STX,
    ETX,
    EOT,
    ENQ,
    ACK,
    CAN,
    MAX_FRAME_SIZE,
)
from database_handler import DatabaseHandler


class TestMusashiDispenser(unittest.TestCase):
    def setUp(self):
        # Create instance with mocked serial port and init_delay=0.0 for speed
        self.patcher = patch('serial.Serial')
        self.mock_serial_cls = self.patcher.start()
        self.mock_ser = MagicMock()
        self.mock_serial_cls.return_value = self.mock_ser
        self.mock_ser.is_open = True
        self.mock_ser.timeout = 2.0
        
        self.dispenser = MusashiDispenser(port="COM_MOCK", init_delay=0.0)

    def tearDown(self):
        self.patcher.stop()

    def test_checksum_calculation_str_bytes_bytearray(self):
        """Test modulo 256 two's complement checksum calculation on str, bytes, and bytearray."""
        cs_str = self.dispenser.compute_checksum("08UL001D01")
        self.assertEqual(cs_str, "C1")

        cs_bytes = self.dispenser.compute_checksum(b"08UL001D01")
        self.assertEqual(cs_bytes, "C1")

        cs_bytearray = self.dispenser.compute_checksum(bytearray(b"08UL001D01"))
        self.assertEqual(cs_bytearray, "C1")

        with self.assertRaises(TypeError):
            self.dispenser.compute_checksum(12345)

    def test_verify_frame_checksum(self):
        """Test verify_frame_checksum length requirement and checksum matching."""
        # Minimum valid frame: 2 len + 2 cmd + 2 CS = 6 chars
        self.assertTrue(self.dispenser.verify_frame_checksum("02A02D"))
        self.assertTrue(self.dispenser.verify_frame_checksum(b"02A02D"))

        # Too short (< 6 characters)
        with self.assertRaises(ValueError):
            self.dispenser.verify_frame_checksum("02A0")

        with self.assertRaises(ValueError):
            self.dispenser.verify_frame_checksum("12345")

        # Checksum mismatch
        with self.assertRaises(ValueError):
            self.dispenser.verify_frame_checksum("02A0FF")

    def test_build_frame(self):
        """Test frame building format: STX + length + cmd + data + CS + ETX."""
        frame = self.dispenser.build_frame("UL", "001D01")
        expected = b'\x0208UL001D01C1\x03'
        self.assertEqual(frame, expected)

    def test_parse_da01_parameters_standard(self):
        """Test parsing DA01 parameters, specifically extracting pressure P in kPa."""
        payload = "21DA01P0100T00100V0050M0NPROD_00001"
        checksum = self.dispenser.compute_checksum(payload)
        full_frame_str = payload + checksum
        
        parsed = self.dispenser.parse_da01_parameters(full_frame_str)
        
        self.assertEqual(parsed['pressure_raw'], 100)
        self.assertEqual(parsed['pressure_kpa'], 10.0)
        self.assertEqual(parsed['time_ms'], 100)
        self.assertEqual(parsed['time_sec'], 0.1)
        self.assertEqual(parsed['vacuum_kpa'], 0.5)
        self.assertEqual(parsed['mode_code'], 0)
        self.assertEqual(parsed['mode_name'], "Timed")
        self.assertEqual(parsed['product_name'], "PROD_00001")

    def test_parse_da01_parameters_dynamic_length_and_whitespace(self):
        """Test dynamic length prefix stripping, space padded numbers, and NUL byte stripping."""
        # 10 chars product name with NUL bytes and spaces
        raw_name = "TEST\x00\x00    "
        self.assertEqual(len(raw_name), 10)
        
        # Space-padded numbers
        content = f"DA01P 100T  250V  50M2N{raw_name}"
        char_count = f"{len(content):02X}"
        payload = char_count + content
        checksum = self.dispenser.compute_checksum(payload)
        full_frame = payload + checksum

        parsed = self.dispenser.parse_da01_parameters(full_frame)
        self.assertEqual(parsed['pressure_raw'], 100)
        self.assertEqual(parsed['pressure_kpa'], 10.0)
        self.assertEqual(parsed['time_ms'], 250)
        self.assertEqual(parsed['vacuum_kpa'], 0.5)
        self.assertEqual(parsed['mode_code'], 2)
        self.assertEqual(parsed['mode_name'], "Sigma Timed")
        self.assertEqual(parsed['product_name'], "TEST")

    def test_handshake_upload(self):
        """Test full 10-step handshake upload flow with STX A0 response in Step 4."""
        payload = "21DA01P0500T00250V0100M2NSIGMA_0001"
        checksum = self.dispenser.compute_checksum(payload)
        frame_bytes = STX + (payload + checksum).encode('ascii') + ETX

        a0_frame_bytes = STX + b"02A02D" + ETX

        read_sequence = [
            ACK,  # Step 2: reply to ENQ
        ]
        for b in a0_frame_bytes:
            read_sequence.append(bytes([b]))

        read_sequence.append(ENQ)  # Step 6: notification ready to send
        
        for b in frame_bytes:
            read_sequence.append(bytes([b]))
            
        read_sequence.append(EOT)  # Step 10: session end EOT
        
        self.mock_ser.read.side_effect = read_sequence

        result = self.dispenser.read_pressure(channel=1)
        
        self.assertEqual(result['channel'], 1)
        self.assertEqual(result['pressure_kpa'], 50.0)
        self.assertEqual(result['time_ms'], 250)
        self.assertEqual(result['mode_name'], "Sigma Timed")

    def test_abort_recovery_on_failure(self):
        """Test protocol abort recovery: sends CAN + EOT + resets buffer on failure."""
        # Fail at Step 2 (timeout or unexpected byte)
        self.mock_ser.read.return_value = b'\x15'  # NAK instead of ACK

        with self.assertRaises(Exception) as ctx:
            self.dispenser.execute_upload_command("UL", "001D01")
        self.assertIn("Handshake failed at Step 2", str(ctx.exception))

        # Check CAN (0x18) and EOT (0x04) were written to serial
        written_bytes = [call.args[0] for call in self.mock_ser.write.call_args_list]
        self.assertIn(CAN, written_bytes)
        self.assertIn(EOT, written_bytes)
        self.assertTrue(self.mock_ser.reset_input_buffer.called)

    def test_step4_a2_error_before_checksum(self):
        """Test Step 4 A2 error frame check occurs before checksum verification."""
        # Dispenser responds with STX, then A2 frame with bogus checksum
        a2_frame = STX + b"02A299" + ETX
        read_sequence = [
            ACK,  # Step 2: reply to ENQ
        ]
        for b in a2_frame:
            read_sequence.append(bytes([b]))
        self.mock_ser.read.side_effect = read_sequence

        with self.assertRaises(Exception) as ctx:
            self.dispenser.execute_upload_command("UL", "001D01")
        self.assertIn("Command Error (A2) returned by Dispenser", str(ctx.exception))

        # Check CAN + EOT written
        written_bytes = [call.args[0] for call in self.mock_ser.write.call_args_list]
        self.assertIn(CAN, written_bytes)
        self.assertIn(EOT, written_bytes)

    def test_step10_clean_eot_handling(self):
        """Test Step 10 completes cleanly without error even if EOT is omitted or timed out."""
        payload = "21DA01P0500T00250V0100M2NSIGMA_0001"
        checksum = self.dispenser.compute_checksum(payload)
        frame_bytes = STX + (payload + checksum).encode('ascii') + ETX
        a0_frame_bytes = STX + b"02A02D" + ETX

        read_sequence = [
            ACK,  # Step 2
        ]
        for b in a0_frame_bytes:
            read_sequence.append(bytes([b]))
        read_sequence.append(ENQ)  # Step 6
        for b in frame_bytes:
            read_sequence.append(bytes([b]))
        read_sequence.append(b'')  # Step 10: dispenser does not send EOT (times out)

        self.mock_ser.read.side_effect = read_sequence
        result = self.dispenser.read_pressure(channel=1)
        self.assertEqual(result['pressure_kpa'], 50.0)

    def test_read_frame_stx_hunting(self):
        """Test read_frame hunts for STX past stray noise bytes."""
        # Noise bytes before STX
        stream = [b'\xff', b'\x00', b'?', STX, b'0', b'2', b'A', b'0', b'2', b'D', ETX]
        self.mock_ser.read.side_effect = stream

        frame = self.dispenser.read_frame(already_read_stx=False)
        self.assertEqual(frame, "02A02D")

    def test_read_frame_max_size_exceeded(self):
        """Test read_frame raises ValueError when frame exceeds MAX_FRAME_SIZE."""
        stream = [STX] + [b'A'] * (MAX_FRAME_SIZE + 5) + [ETX]
        self.mock_ser.read.side_effect = stream

        with self.assertRaises(ValueError) as ctx:
            self.dispenser.read_frame(already_read_stx=False)
        self.assertIn("exceeded maximum allowed size", str(ctx.exception))

    def test_read_pressure_channel_bounds(self):
        """Test channel bounds checking (1 to 100)."""
        with self.assertRaises(ValueError):
            self.dispenser.read_pressure(channel=0)
        with self.assertRaises(ValueError):
            self.dispenser.read_pressure(channel=101)


class TestMockMusashiDispenser(unittest.TestCase):
    def setUp(self):
        self.mock_dispenser = MockMusashiDispenser(port="MOCK", init_delay=0.0)

    def test_mock_dispenser_payload_and_parsing(self):
        """Test mock dispenser produces a payload that validates and parses successfully."""
        data = self.mock_dispenser.read_pressure(channel=1)
        self.assertEqual(data['channel'], 1)
        self.assertEqual(data['product_name'], "PROD_MOCK")
        self.assertEqual(data['mode_name'], "Sigma Timed")

        # Parse raw payload with parse_da01_parameters
        parsed = self.mock_dispenser.parse_da01_parameters(data['raw_payload'])
        self.assertEqual(parsed['product_name'], "PROD_MOCK")
        self.assertEqual(parsed['pressure_kpa'], data['pressure_kpa'])
        self.assertEqual(parsed['time_ms'], data['time_ms'])
        self.assertEqual(parsed['vacuum_kpa'], data['vacuum_kpa'])

        # Verify checksum on mock raw_payload
        self.assertTrue(self.mock_dispenser.verify_frame_checksum(data['raw_payload']))

    def test_mock_dispenser_channel_bounds(self):
        """Test channel bounds check on mock dispenser."""
        with self.assertRaises(ValueError):
            self.mock_dispenser.read_pressure(channel=0)
        with self.assertRaises(ValueError):
            self.mock_dispenser.read_pressure(channel=101)

    def test_mock_dispenser_api_parity(self):
        """Test mock dispenser has matching helper methods."""
        frame = self.mock_dispenser.build_frame("UL", "001D01")
        self.assertEqual(frame, b'\x0208UL001D01C1\x03')
        cs = self.mock_dispenser.compute_checksum("08UL001D01")
        self.assertEqual(cs, "C1")
        self.assertTrue(self.mock_dispenser.verify_frame_checksum("02A02D"))
        self.assertEqual(self.mock_dispenser.read_frame(), "02A02D")
        upload_resp = self.mock_dispenser.execute_upload_command("UL", "001D01")
        self.assertTrue(self.mock_dispenser.verify_frame_checksum(upload_resp))


class TestResolveSerialPort(unittest.TestCase):
    @patch('serial.tools.list_ports.comports')
    def test_windows_no_hijack(self, mock_comports):
        """Test Windows does not hijack a requested COM port to another port."""
        mock_port = MagicMock()
        mock_port.device = "COM1"
        mock_comports.return_value = [mock_port]

        with patch('sys.platform', 'win32'):
            # Explicit COM3 requested - should NOT be hijacked to COM1
            res = resolve_serial_port("COM3")
            self.assertEqual(res, "COM3")

            # AUTO requested - should resolve to COM1
            res_auto = resolve_serial_port("AUTO")
            self.assertEqual(res_auto, "COM1")

            # /dev/ path requested on Windows - should resolve to COM1
            res_dev = resolve_serial_port("/dev/cu.usbserial-123")
            self.assertEqual(res_dev, "COM1")

    @patch('serial.tools.list_ports.comports')
    def test_linux_resolution(self, mock_comports):
        """Test Linux resolves macOS /dev/cu.usbserial path to detected ttyUSB/ttyACM."""
        mock_port = MagicMock()
        mock_port.device = "/dev/ttyUSB0"
        mock_comports.return_value = [mock_port]

        with patch('sys.platform', 'linux'):
            res = resolve_serial_port("/dev/cu.usbserial-A600bsZD")
            self.assertEqual(res, "/dev/ttyUSB0")


class TestDatabaseHandler(unittest.TestCase):
    def setUp(self):
        self.test_db_path = "test_musashi_data.db"
        if os.path.exists(self.test_db_path):
            try:
                os.remove(self.test_db_path)
            except Exception:
                pass
        self.db_config = {
            "db_type": "sqlite",
            "db_name": self.test_db_path,
            "table_name": "test_telemetry",
            "description": "Test Database"
        }
        self.db_handler = DatabaseHandler(self.db_config)

    def tearDown(self):
        self.db_handler.close()
        if os.path.exists(self.test_db_path):
            try:
                os.remove(self.test_db_path)
            except Exception:
                pass

    def test_database_init_and_insert(self):
        sample_data = {
            "channel": 1,
            "pressure_kpa": 12.5,
            "pressure_raw": 125,
            "time_ms": 500,
            "time_sec": 0.5,
            "vacuum_kpa": 0.2,
            "mode_code": 0,
            "mode_name": "Timed",
            "product_name": "PROD_TEST",
            "raw_payload": "21DA01P0125T00500V0020M0NPROD_TEST  XX"
        }
        
        row_id = self.db_handler.insert_telemetry(sample_data)
        self.assertIsNotNone(row_id)
        
        # Verify stored record via sqlite query
        conn = sqlite3.connect(self.test_db_path)
        cursor = conn.cursor()
        cursor.execute(f"SELECT channel, pressure_kpa, mode_name, product_name FROM test_telemetry WHERE id=?", (row_id,))
        row = cursor.fetchone()
        conn.close()
        
        self.assertEqual(row[0], 1)
        self.assertEqual(row[1], 12.5)
        self.assertEqual(row[2], "Timed")
        self.assertEqual(row[3], "PROD_TEST")

    def test_load_config(self):
        cfg = load_config("config.json")
        self.assertIn("serial", cfg)
        self.assertIn("database", cfg)
        self.assertIn("acquisition", cfg)
        self.assertIn("interval_time", cfg["acquisition"])
        self.assertIn("description", cfg["database"])


if __name__ == "__main__":
    unittest.main()
