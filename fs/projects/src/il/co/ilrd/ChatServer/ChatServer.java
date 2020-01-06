package il.co.ilrd.ChatServer;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectableChannel;
import java.nio.channels.SelectionKey;
/*
 * Protocols for setting and maintaining client - server communication: 
 * 
 * 	 	1 - "<con:[usr_name]>" (for example "<con:Dr.Piglet>" )
 * 			asks from server to connect user 
 * 			server will return a unique token to the user in format of <con:[token]> (for example <con:%@621afrat52>)
 * 			
 * 		2 - "<dis:[token]>" - servers closes connection with the message sender and removes him from map
 * 
 * 		3 - all other messages will be sent with the prefix <msg:[token][name]:[msg]> to everyone including sender
 * 
 */

import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Random;
import java.util.Set;

public class ChatServer {
	private HashMap <String,Peer > namesMap = new HashMap<>(); 
	private Selector selector; 
	private ServerSocketChannel serverSocket;
	private static int MSG_BUFFER_SIZE = 1024;
	private int port;
	private boolean toRun = false; 
	private InetSocketAddress address; 
	
		//CONSTRUCTOR
	/*--------------------------------------------------------------------*/
	protected ChatServer (int port, String addressIP) throws IOException {
		namesMap = new HashMap<>(); 
		this.port = port; 
		serverSocket = ServerSocketChannel.open(); 
		selector = Selector.open();
		serverSocket.configureBlocking(false); 
		address = new InetSocketAddress(addressIP, this.port); 
	}
	
	/*-------------------------------------------------------------------*/
	private static class Peer{
		private String name; 
		private SelectableChannel channel; 
		
		private Peer(String name, SelectableChannel channel, String token) {
			this.name = name; 
			this.channel = channel; 
		}
		
		private void send(String message) throws IOException {
			message = "<msg:" + message +">"; 
			ByteBuffer msgBuff = ByteBuffer.wrap(message.getBytes());
		 ((SocketChannel)channel).write(ByteBuffer.wrap(message.getBytes()));  
		 	msgBuff.clear();
		}
		
		private void disconnect() {
			try {
				((SocketChannel)channel).close();
			}catch (Exception e) {
				// TODO: handle exception
			}
		}	
	}
	
	/*-------------------------------------------------------------------*/
	private void broadcast(String message) {
		for (Peer p : namesMap.values()) {
			try {
				p.send(message);
			
			}catch (Exception e) {
			}
		}
	}
	
	/*-----------------------------------------------------------*/
	private void runMainLoop() throws Exception {
		SelectionKey sKey;
		Set<SelectionKey> selectedKeys;
		Iterator<SelectionKey> itr;
		SelectableChannel peerSocketChannel;
		
		String message = null;
		
		//initiate selector					
		serverSocket.bind(address);
		serverSocket.register(selector, SelectionKey.OP_ACCEPT);
		
		//run server application
		ServerWindow.printToConsole("Server Up");
		while (toRun){		
			selector.select();
			selectedKeys = selector.selectedKeys();  
	        itr = selectedKeys.iterator();  
	       
            while (itr.hasNext()){  
            	sKey = (SelectionKey) itr.next();  
            	peerSocketChannel = sKey.channel();  
            	
                if (sKey.isAcceptable())
                {  
                	accept(peerSocketChannel);
                }  
                
                else if (sKey.isReadable()) 
                {  
                	handleMsg(peerSocketChannel, message, sKey); 
                }     

                itr.remove();  
                Thread.sleep(100);
            }  
		}
	}
		
	/*
	 * accepts connection to socket 
	 */
	private void accept(SelectableChannel channel) throws Exception {

		channel = serverSocket.accept(); 
		channel.configureBlocking(false); 
		channel.register(selector, SelectionKey.OP_READ); 	
	}

	/*
	 * handles new user connection 
	 * removal of users
	 * sending messages to all / broadcasting
	 */
	private void handleMsg(SelectableChannel channel, String message, SelectionKey sKey) throws IOException {
		String usrToken;
		ByteBuffer msgBuffer = ByteBuffer.allocate(MSG_BUFFER_SIZE); 
		msgBuffer.clear(); 
		((SocketChannel)channel).read(msgBuffer); 
		message = new String(msgBuffer.array()).trim();   
		
		if (isNewUser(message)) {
			addNewUser(message, channel);
		}
		else if (isRemoveUser(message)) {
			removeUserFromChat(message, sKey); 
		}
		else {
			usrToken = getToken(message); 
			if(namesMap.containsKey(usrToken)) {
				message = namesMap.get(usrToken).name + ": " + getMessage(message); 
				//ServerWindow.printToConsole(message);
				broadcast(message);
			}
		}
	}
	
	/*
	 * retrieves token from user
	 * null if unable
	 */
	private String getToken(String message) {
		try {
		return message.substring(message.indexOf(":") + 1, message.indexOf(","));
		
		}catch (Exception e) {return null; }
	}
	/*
	 * parses message
	 */
	private String getMessage(String line) {
		return line.substring(line.indexOf(",") + 1, line.indexOf(">")); 
	}
	
	/*
	 * creates new peer add it to users map
	 * return to user "<con:[newly generated token]>" 
	 */
	private void addNewUser(String message, SelectableChannel channel) throws IOException{
		
		String name = message.substring(message.indexOf(':') + 1, message.indexOf('>')); 
		String token = generateToken();
		//ServerWindow.printToConsole(token);
		namesMap.put(token, new Peer(name, channel, token));
		String returnMessage = "<con:" + token + ">"; 
		
		((SocketChannel)channel).write(ByteBuffer.wrap(returnMessage.getBytes()));  
		broadcast(name + " "+"has joined us");
	}

	/*
	 * basically a random string token for each user, unlikely to have duplicates (Very unlikely)
	 */
	private String generateToken() {
		String ALPHA_NUMERICAL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefjhijklmnopqrstuvwxyz"; 
		char[] text = new char[8]; 
		for (int i = 0; i < text.length; i++) {
			 text[i] = ALPHA_NUMERICAL.charAt((new Random().nextInt(ALPHA_NUMERICAL.length()))); 
		}
		
		return new String(text);
	}
	
	/*
	 * returns true for connect msg from user
	 */
	private boolean isNewUser(String message) {
		return message.startsWith("<con:"); 
	}
	
	/*
	 * returns true for disconnect msg from user
	 */
	
	private boolean isRemoveUser(String message) {
		return message.startsWith("<dis:"); 
	}
	
	/*
	 * removes user , closes channel and key 
	 */
	private void removeUserFromChat(String message, SelectionKey sKey) {
		String token = getToken(message);
		sKey.cancel();
		namesMap.get(token).disconnect();
		broadcast(namesMap.remove(token).name + " has left"); 
		//ServerWindow.printToConsole(token + " has left");
	}
	/*
	 * method for starting server
	 * being used by ServerWindow startButton 
	 */
	protected void start() {
		toRun = true; 
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				try {
					runMainLoop();
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}).start();
	}
	
	/*
	 * stops servers
	 * closes connection and channel
	 */
	protected void stop() {
		toRun = false; 
		try {
			serverSocket.close(); 
			selector.close();
			System.exit(0);
		}catch (Exception e) {
			// TODO: handle exception
		}
	}
	
}
