package il.co.ilrd.SQL;

import il.co.ilrd.CRUD.LogMonitor;

public class MonitoringSQL  {
	
	public static void main(String[] args) throws Exception{
		LogMonitor l = new LogMonitor("/var/log/syslog");
		String url = "jdbc:mysql://10.1.0.83:3306/";
		CRUDSQL q = new CRUDSQL(url , "root", "password" , "Syslog", "Log");
		
		l.register((t,s)->{
			q.create((String)s); 	
			;}); 
		l.startMonitoring();
		Thread.sleep(1000);
		l.stopMonitoring();
		q.close(); 	
	}
	
	
}
