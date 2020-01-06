package il.co.ilrd.ChatServer;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;

import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

@SuppressWarnings("unused")
public class ChatClient{

		private String clientName;
		private int destPort;
		private String token;
		private SocketChannel socket;
		private ByteBuffer buffer; 
		private boolean running = false; 
		
		/**
		 * @throws InterruptedException ************************************************************************/
		/*
		 * creates a new client
		 * ip and port is recieved from user 
		 */
		protected ChatClient(String name, String ip, int destPort) throws InterruptedException
		{
			try {
			clientName = name;
			this.destPort = destPort;
			socket = SocketChannel.open(new InetSocketAddress(ip, destPort));
			buffer = ByteBuffer.allocate(1024); 
			
			}catch (Exception e) {
				ClientWindow.printErrMsg();
				Thread.sleep(5000);
				System.exit(1);
			}
		}

		/********************************************************************************************/
		protected void sendMessage(String line) throws IOException {
		    sendToServer("<msg:" + token +"," + line + ">");
		}
		private void sendConnectMsg() throws IOException {
			sendToServer("<con:" + clientName + ">");
		}
		
		private void sendDisconnectMsg() throws IOException {
			sendToServer("<dis:" + token + "," + ">");
		}
		
			//actually sends the message to server
		private void sendToServer(String messageToSend) throws IOException{
			buffer.clear(); 
			buffer.put(messageToSend.getBytes());
			buffer.flip();
			socket.write(buffer);
		//	buffer.clear();
		}
		
		/**************************************************************************************************/
		
		private void sendConnectRequest() throws IOException{
			buffer.clear(); 
			String line;
			sendConnectMsg();
			socket.read(buffer); 
				//Gets response from server
			line = new String(buffer.array()).trim();
				//truncats token
			this.token = getToken(line);  
			buffer.clear(); 
		}
		
		private String getToken(String message) {
			return message.substring(message.indexOf(":") + 1, message.indexOf(">"));
		}
		
		/******************************************************************************/
		protected void start() throws IOException, InterruptedException{
			sendConnectRequest();
			if (!running) {
				running = true; 
				listen(); 
			}
		}
		
		/*
		 * listening thread for getting msg from server
		 */
		private void listen() {
			new Thread(()-> {
				ByteBuffer buffer = ByteBuffer.allocate(1024);
				int currBytes = 0; 
				while (running) {
					try {
						buffer.clear(); 
						currBytes = socket.read(buffer); 
						if (currBytes == -1) {
							break; 
						}
						String newLine = new String(buffer.array()).trim();
						String message = newLine.substring(newLine.indexOf(":")+ 1, newLine.indexOf(">"));
						
						ClientWindow.printToConsole(message);
						buffer.clear(); 
					}catch (Exception e) {
						// TODO: handle exception
					}
				}
			}).start(); 
		}	
	
	protected String getClientName() {
		return new String(clientName); 
	}
	
	protected void disconnect() {
		try {
			sendDisconnectMsg();
			running = false; 
			socket.close();
		} catch (IOException e) {
			e.printStackTrace();
		} 
	}
}
