package networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

import il.co.ilrd.CRUD.CRUDFile;

public class UDPEchoServer extends Thread{
	  private DatagramSocket socket;
      private boolean toRun;
      private byte[] buffer= new byte[1024];
      private CRUDFile file; 
      
      public UDPEchoServer() throws SocketException{
    	  socket = new DatagramSocket(4445); 
    	  this.file = file; 
      }
      
     @Override
    public void run() {
    	 toRun = true; 
    	 DatagramPacket packet  = new DatagramPacket(buffer, buffer.length);
         try {
	        	 while(toRun) {
					socket.receive(packet);
					InetAddress address = packet.getAddress(); 
					int port = packet.getPort();
					packet = new DatagramPacket(buffer, buffer.length, address, port); 
					String recieved = new String(packet.getData(), 0, packet.getLength()); 
					
					if (recieved.equals("end")) {
						toRun = false; 
						continue; 
					}
					
					file.create(recieved); 
	        	 }
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
}
