package il.co.ilrd.ChatServer;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.UIManager;


import javax.swing.JScrollPane;
import java.awt.BorderLayout;
import javax.swing.JTextArea;
import javax.swing.JButton;
import javax.swing.JPanel;
import java.awt.FlowLayout;

import javax.swing.JTextField;
import java.awt.Font;
import java.io.IOException;
import java.net.UnknownHostException;
import java.awt.Color;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import javax.swing.SwingConstants;

public class ClientWindow {

	private JFrame frame;
	private JTextField message;
    private static JTextArea textArea = new JTextArea();
    private ChatClient client; 
    private JTextField txtUserName;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
					ClientWindow window = new ClientWindow();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 * @throws IOException 
	 * @throws UnknownHostException 
	 * @throws InterruptedException 
	 */
	public ClientWindow() throws UnknownHostException, IOException, InterruptedException {
		initialize();
		String name = JOptionPane.showInputDialog("Enter name");
		String ip = JOptionPane.showInputDialog("Enter Servers IP"); 
		String portMsg = JOptionPane.showInputDialog("Enter Server's port");
		int port = Integer.parseInt(portMsg); 
		frame.setTitle("Chat room - IP is: " + ip);
		
		client = new ChatClient(name ,ip , port);
		
	}
	
	public static void printErrMsg() {
		JOptionPane.showMessageDialog(null, "Error Connecting, please check ip/port"); 
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setFont(new Font("Dialog", Font.PLAIN, 13));
		frame.setForeground(Color.BLACK);
		frame.setTitle("Chat Room");
		frame.setBounds(100, 100, 720, 640);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new BorderLayout(0, 0));
		
		frame.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				client.disconnect();
				System.exit(0);
				
			}
		});
		textArea.setBackground(Color.ORANGE);
		textArea.setEditable(false);
		JScrollPane scrollPane = new JScrollPane(textArea);
		frame.getContentPane().add(scrollPane);
		frame.getContentPane().add(scrollPane, BorderLayout.CENTER);
		
		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.SOUTH);
		panel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
		JButton btnSend = new JButton("Send");
		message = new JTextField();
		message.setFont(new Font("Dialog", Font.BOLD, 14));
		panel.add(message);
		message.setColumns(35);
		panel.add(btnSend);
		
		JPanel panel_1 = new JPanel();
		frame.getContentPane().add(panel_1, BorderLayout.NORTH);
		
		JButton btnDisconnect = new JButton("Disconnect");
		btnDisconnect.addActionListener((s)->{
				client.disconnect();
				try {
					Thread.sleep(1000);
					System.exit(0);
				} catch (InterruptedException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				
				btnDisconnect.setEnabled(false);
			;});
				
				
		btnDisconnect.setEnabled(false);
		
		JButton btnConnect = new JButton("Connect");
		btnConnect.setHorizontalAlignment(SwingConstants.RIGHT);
		btnConnect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				//Connect user to chat
				try {
					txtUserName.setText(client.getClientName());
					txtUserName.setSelectedTextColor(Color.RED);
					btnConnect.setEnabled(false);
					btnDisconnect.setEnabled(true);
					client.start();
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
		
		txtUserName = new JTextField();
		txtUserName.setFont(new Font("SansSerif", Font.BOLD, 20));
		txtUserName.setText("Username : ");
		panel_1.add(txtUserName);
		txtUserName.setColumns(20);
		
		
		panel_1.add(btnDisconnect);
		panel_1.add(btnConnect);
		
		btnSend.addActionListener(e->{
			if(!message.getText().equals("")) {
			try {
				client.sendMessage(message.getText());
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			message.setText(" ");
			}
			;});;
		
		frame.setLocationRelativeTo(null);
	}
	
	public static void printToConsole(String message) {
		System.out.println(message);
		System.out.println("hello");
		textArea.setText(textArea.getText() + message+ "\n");
	}

}