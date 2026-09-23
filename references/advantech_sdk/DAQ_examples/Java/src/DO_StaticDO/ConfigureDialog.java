package DO_StaticDO;

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

import Automation.BDaq.BDaqApi;
import Automation.BDaq.DeviceTreeNode;
import Automation.BDaq.ErrorCode;
import Automation.BDaq.EthManagedEdge;
import Automation.BDaq.InstantDoCtrl;

import javax.swing.JFormattedTextField;

import Common.*;


public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	private final JPanel contentPanel = new JPanel();
	private JComboBox cmbDevice;
	private JComboBox cmbHostName;	
	private JButton btnLogin;
	private JButton btnOK;
	
	public boolean isFirstLoad = true;
	public InstantDoCtrl instantDoCtrl = new InstantDoCtrl();
	
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	private String localEdge = "Local";
	
	/**
	 * 
	 *Build Date:2011-9-20
	 *Author:Administrator
	 *Function Description: Create the dialog.
	 */
	public ConfigureDialog(StaticDO parent) {
		super(parent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setTitle("Static DO - Configuration");
		setBounds(100, 100, 323, 209);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		cmbDevice = new JComboBox();
		cmbDevice.setBounds(73, 51, 226, 21);
		contentPanel.add(cmbDevice);
		
		JLabel lblDevice = new JLabel("Device:");
		lblDevice.setBounds(20, 54, 45, 15);
		contentPanel.add(lblDevice);
		
		btnOK = new JButton("OK");
		btnOK.setBounds(104, 137, 69, 23);
		btnOK.addActionListener(new ButtonOKActionListener());
		contentPanel.add(btnOK);
		
		JButton btnCancel = new JButton("Cancel");
		btnCancel.setBounds(214, 137, 75, 23);
		btnCancel.addActionListener(new ButtonCancelActionListener());
		contentPanel.add(btnCancel);
		
		JLabel lblProfilePath = new JLabel("Profile:");
		lblProfilePath.setBounds(20, 97, 54, 15);
		contentPanel.add(lblProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(214, 93, 85, 23);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		contentPanel.add(btnBrowse);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(73, 94, 131, 20);
		contentPanel.add(txtProfilePath);
		
		JLabel lblHostName = new JLabel("Host name:");
		lblHostName.setBounds(10, 21, 65, 15);
		contentPanel.add(lblHostName);
		
		cmbHostName = new JComboBox();
		cmbHostName.setEditable(true);
		cmbHostName.setBounds(73, 18, 137, 21);
		contentPanel.add(cmbHostName);
		
		btnLogin = new JButton("Login");
		btnLogin.setBounds(219, 18, 80, 23);
		btnLogin.addActionListener(new ButtonLoginActionListener());
		contentPanel.add(btnLogin);		

		InitializateHostNameComboBox();
		cmbHostName.addItemListener(new ComboBoxHostNameItemListener());
		cmbHostName.getEditor().getEditorComponent().addKeyListener(new EditorHostNameKeyListener());
		
		Initialization();
	}
	
	/**
	 * 
	 *Build Date:2011-9-20
	 *Author:Administrator
	 *Function Description: this function is used to initialize the configure dialog.
	 */
	private void Initialization(){
		cmbDevice.removeAllItems();
		
		ArrayList<DeviceTreeNode> installedDevice = instantDoCtrl.getSupportedDevices();
		
		if(installedDevice.size() <= 0){
			ShowMessage("No device to support the currently demonstrated function!");
			SetEditUIEnable(false);
			return;
			//System.exit(0);
		}else{
			for(DeviceTreeNode installed : installedDevice){
				cmbDevice.addItem(installed.toString());
			}
			cmbDevice.setSelectedIndex(0);
		}
	}
	
	/**
	 * 
	 *Build Date:2011-9-20
	 *Author:Administrator
	 *Function Description: this function is used to get device name.
	 * @return String device name
	 */
	public String GetDeviceName(){
		return cmbDevice.getSelectedItem().toString();
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
	 * Build Date:2011-9-20
	 * Author:Administrator
	 * Function Description: This function is used to show the error massage to user!
	 * 
	 * @param message: the message shown to users!
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox",
				JOptionPane.WARNING_MESSAGE);
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the OK button's action! 
	 */
	class ButtonOKActionListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0) {
			StaticDO parent = (StaticDO) getParent();
			parent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parent.configure.hostName = cmbHostName.getSelectedItem().toString();
			parent.Initialization();
			parent.setVisible(true);
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
		btnBrowse.setEnabled(enable);
		txtProfilePath.setEnabled(enable);
		btnOK.setEnabled(enable);
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
				instantDoCtrl.Logout();
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
			instantDoCtrl.Logout();
			String hostName = cmbHostName.getSelectedItem().toString();
			if (!hostName.equals(localEdge)) {
				if (ErrorCode.Success == instantDoCtrl.Login(hostName)) {
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
			instantDoCtrl.Logout();
			if (isLocal) {
				Initialization();
			}
		}		
		
	}
}
