package il.co.ilrd.CRUD;

public class MonitorApp {

	public static void main(String[] args) {
		try {
		    
			LogMonitor l = new LogMonitor("/var/log/syslog");
			CRUDFile backup = new CRUDFile("/home/student/git/fs/projects/src/il/co/ilrd/CRUD/logfile.txt");
					
			
			l.register((t,s)->{
				backup.create((String)s); 	
				;}); 
			
			l.startMonitoring(); 
			Thread.sleep(15000);
			l.stopMonitoring();
			backup.close();	
		
		}catch (Exception e) {}
	}
	
	
}
