package networking;

import il.co.ilrd.CRUD.CRUDFile;
import il.co.ilrd.CRUD.LogMonitor;

public class UDPTest{
	public static void main(String[] args) throws Exception{
		CRUDFile backup = new CRUDFile("/home/student/git/fs/projects/src/il/co/ilrd/networking/logfile.txt");
		UDPEchoServer server = new UDPEchoServer(backup); 
		UDPClient client = new UDPClient(); 
		LogMonitor l = new LogMonitor("/var/log/syslog");
		
		server.start();
		l.register((s,t)->{
			
			
			;});
		
		
		String echo = client.sendEcho("Hello"); 
		System.out.println(echo);
		System.out.println("x");
	}
	
	
	
}

