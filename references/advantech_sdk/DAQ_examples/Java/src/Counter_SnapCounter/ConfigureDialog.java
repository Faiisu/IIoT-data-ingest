package Counter_SnapCounter;

import java.awt.BorderLayout;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.net.MalformedURLException;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.filechooser.FileNameExtensionFilter;

import Automation.BDaq.*;
import Common.ClassLoaderUtil;

import javax.swing.JFormattedTextField;

//import org.eclipse.wb.swing.FocusTraversalOnArray;
//import java.awt.Component;

public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private final JPanel contentPanel = new JPanel();
	private JComboBox cmbDevice;
	private JComboBox cmbChannel;
	private JComboBox cmbCountingType;
	private JButton btnOK;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	public boolean isFirstLoad = true;
	private JLabel lblHostName;
	private JComboBox cmbHostName;
	private JButton btnLogin;
	
	private String localEdge = "Local";
	UdCounterCtrl udCounterCtrl = new UdCounterCtrl();

	/**
	 * 
	 * Build Date:2011-10-12
	 * Author:Administrator
	 * Function Description: Create the dialog.
	 */
	public ConfigureDialog(SnapCounter parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setTitle("Snap Counter - Configuration");
		setResizable(false);
		setBounds(100, 100, 346, 272);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);		

		JLabel lblNewLabel = new JLabel("Device:");
		lblNewLabel.setBounds(10, 53, 50, 15);
		contentPanel.add(lblNewLabel);

		JLabel lblChannelStart = new JLabel("<html><body>Counter<br>Channel:</body></html>");
		lblChannelStart.setBounds(10, 113, 44, 42);
		contentPanel.add(lblChannelStart);
		
		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDiveceItemListener());
		cmbDevice.setBounds(64, 50, 257, 21);
		contentPanel.add(cmbDevice);
		
		cmbChannel = new JComboBox();
		cmbChannel.setBounds(64, 119, 257, 21);
		contentPanel.add(cmbChannel);
		
		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(143, 195, 75, 23);
		getRootPane().setDefaultButton(btnOK);
		contentPanel.add(btnOK);

		JButton btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(246, 195, 75, 23);
		contentPanel.add(btnCancel);
		
		JLabel lblCountingType = new JLabel("<html><body>Counting<br>Type:</body></html>");
		lblCountingType.setBounds(10, 156, 51, 28);
		contentPanel.add(lblCountingType);
		
		cmbCountingType = new JComboBox();
		cmbCountingType.setBounds(64, 158, 257, 21);
		contentPanel.add(cmbCountingType);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(10, 89, 52, 15);
		contentPanel.add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(64, 86, 135, 20);
		contentPanel.add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(232, 86, 89, 23);
		contentPanel.add(btnBrowse);
		
		lblHostName = new JLabel("Host name:");
		lblHostName.setBounds(5, 20, 65, 15);
		contentPanel.add(lblHostName);
		
		cmbHostName = new JComboBox();
		cmbHostName.setEditable(true);
		cmbHostName.setBounds(66, 15, 166, 21);
		contentPanel.add(cmbHostName);
		
		btnLogin = new JButton("Login");
		btnLogin.setBounds(241, 15, 80, 23);
		contentPanel.add(btnLogin);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		
		btnLogin.addActionListener(new ButtonLoginActionListener());
		InitializateHostNameComboBox();
		cmbHostName.addItemListener(new ComboBoxHostNameItemListener());
		cmbHostName.getEditor().getEditorComponent().addKeyListener(new EditorHostNameKeyListener());
		
		Initialization();
	}
	
	/**
	 * 
	 * Build Date:2011-10-12
	 * Author:Administrator
	 * Function Description: This function is used to initialize the Configuration dialog.
	 */
	protected void Initialization() {
		cmbDevice.removeAllItems();
		cmbChannel.removeAllItems();
		cmbCountingType.removeAllItems();
		
		ArrayList<DeviceTreeNode> installedDevice = udCounterCtrl.getSupportedDevices();

		if (installedDevice.size() <= 0) {
			ShowMessage("No device to support the currently demonstrated function!");
			SetEditUIEnable(false);
			return;
			//System.exit(0);
		} else {
			for (DeviceTreeNode installed : installedDevice) {
				cmbDevice.addItem(installed.toString());
			}
			cmbDevice.setSelectedIndex(0);
		}
	}
	
	/**
	 * 
	 * Build Date:2011-10-12
	 * Author:Administrator
	 * Function Description: If some errors occurred, Show the error code to the users.
	 * 
	 * @param message:the message shown to users!
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox",
				JOptionPane.WARNING_MESSAGE);
	}
	
	/**
	 * 
	 *Build Date:2016-2-25
	 *Author:Administrator
	 *Function Description: this function is used to get profile path.
	 * @return String device name
	 */
	public String GetProfilePath() {
		return txtProfilePath.getText();
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the device comboBox's
	 * 							   item selected changing action! 
	 */
	class ComboBoxDiveceItemListener implements ItemListener{
		public void itemStateChanged(ItemEvent e) {
			if (cmbDevice.getItemCount() < 1) { 
				return; 
			}
			String selected = ((JComboBox) e.getSource()).getSelectedItem().toString();
			if (e.getStateChange() == ItemEvent.SELECTED) {
				btnOK.setEnabled(true);
				try {
					
					// Set channel start combo box
					udCounterCtrl.setSelectedDevice(new DeviceInformation(selected));
					int channelCountMax = udCounterCtrl.getFeatures().getChannelCountMax();
					CounterCapabilityIndexer capabilityIndexer = udCounterCtrl.getFeatures().getCapabilities();
					
					for(int i = 0; i < channelCountMax; i++){
						CounterCapability[] capability = capabilityIndexer.getItem(i);
						for(CounterCapability cap : capability){
							if(cap == CounterCapability.UpDownCount){
								cmbChannel.addItem(String.valueOf(i));
							}
						}
					}
					cmbChannel.setSelectedIndex(0);
					
					//Set Counting type for selected device
					int cntTypeCount = udCounterCtrl.getFeatures().getUdCountingTypes().length;
					CountingType[] countingType = udCounterCtrl.getFeatures().getUdCountingTypes();
					for (int i = 0; i < cntTypeCount; i++) {
						cmbCountingType.addItem(countingType[i]);
					}
					cmbCountingType.setSelectedIndex(0);
								
					udCounterCtrl.Cleanup();
				}catch (Exception except) {
					ShowMessage("Sorry, there're some errors occured: " + except.toString());
					btnOK.setEnabled(false);
					return;
				}
			}else{
				cmbChannel.removeAllItems();
				cmbCountingType.removeAllItems();
				return;
			}
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the OK button's action! 
	 */
	class ButtonOKActionListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0) {
			SnapCounter parrent = (SnapCounter)getParent();
			parrent.configure.hostName = cmbHostName.getSelectedItem().toString();
			parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parrent.configure.counterChannel = Integer.parseInt(cmbChannel.getSelectedItem().toString());
			parrent.configure.cntType = (CountingType) cmbCountingType.getSelectedItem();
			
			parrent.Initialization();
			parrent.setVisible(true);
			setVisible(false);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the Cancel button's action! 
	 */
	class ButtonCancelActionListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0) {
			if (isFirstLoad) {
				System.exit(0);
			} else {
				setVisible(false);
			}
		}
	}
	
	class ButtonBrowseActionListener implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			//
			String str = null;
			try {
				str = ClassLoaderUtil.getExtendResource("../../profile");
			} catch (MalformedURLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			str = str.substring(6);
			
			//open file dialog to select profile
			JFileChooser chooser = new JFileChooser(new File(str));
			chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
			chooser.setFileFilter(new FileNameExtensionFilter("Licence File(.xml)", "xml"));
			chooser.showOpenDialog(new JLabel());
			File file=chooser.getSelectedFile();
			txtProfilePath.setText(file.getAbsolutePath());
		}	
	}

	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the configure dialog's closing event.
	 */
	class WindowCloseActionListener extends WindowAdapter{
		@Override
		public void windowClosing(WindowEvent e) {
			if (isFirstLoad) {
				System.exit(0);
			}
		}
	}
	
	/**
	 * 
	 *Build Date:2024-8-28
	 *Author:Administrator
	 *Function Description: This function is used to initialize the ComboBox
	 *                      hostName's list.
	 */
	private void InitializateHostNameComboBox() {
		cmbHostName.removeAllItems();
		cmbHostName.addItem(localEdge);
		ArrayList<EthManagedEdge> managedEdges = BDaqApi.AdxQueryManagedEdgeList();
		for (EthManagedEdge edge : managedEdges) {
			cmbHostName.addItem(edge.EdgeName);
		}
	}
	
	/**
	 * 
	 *Build Date:2024-8-28
	 *Author:Administrator
	 *Function Description: This function is used to set component enabled.
	 */
	protected void SetEditUIEnable(boolean enable) {
		cmbDevice.setEnabled(enable);
		cmbChannel.setEnabled(enable);
		btnOK.setEnabled(enable);
		btnBrowse.setEnabled(enable);
		txtProfilePath.setEnabled(enable);
	}
	
	/**
	 * 
	 *Build Date:2024-8-28
	 *Author:Administrator
	 *Function Description: This class is used to listen the comboBox 
	 *                      hostName's items selecting changed action.
	 */
	class ComboBoxHostNameItemListener implements ItemListener{
		@Override
		public void itemStateChanged(ItemEvent e) {
			String selected = ((JComboBox) e.getSource()).getSelectedItem().toString();
			if (e.getStateChange() == ItemEvent.SELECTED) {
				boolean isLocal = selected.equals(localEdge);
				SetEditUIEnable(isLocal);
				udCounterCtrl.Logout();
				if (isLocal) {
					Initialization();
				}
			}
		}
	}
	
	/**
	 * 
	 *Build Date:2024-8-28
	 *Author:Administrator
	 *Function Description: This class is used to listen the button 
	 *                      login's action.
	 */
	class ButtonLoginActionListener implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			udCounterCtrl.Logout();
			String hostName = cmbHostName.getSelectedItem().toString();
			if (!hostName.equals(localEdge)) {
				if (ErrorCode.Success == udCounterCtrl.Login(hostName)) {
					SetEditUIEnable(true);
					Initialization();
				}				
			}
		}	
	}
	
	/**
	 * 
	 *Build Date:2024-8-28
	 *Author:Administrator
	 *Function Description: This class is used to listen the comboBox 
	 *                      hostName's items text changed action.
	 */
	class EditorHostNameKeyListener implements KeyListener{
		
		@Override
		public void keyTyped(KeyEvent e) {
			// TODO Auto-generated method stub
		}
		
		@Override
		public void keyPressed(KeyEvent e) {
			// TODO Auto-generated method stub
		}
		
		@Override
		public void keyReleased(KeyEvent e) {
			// TODO Auto-generated method stub
			String hostName = cmbHostName.getEditor().getItem().toString();
			boolean isLocal = hostName.equals(localEdge);
			SetEditUIEnable(isLocal);
			udCounterCtrl.Logout();
			if (isLocal) {
				Initialization();
			}
		}
	}
}
