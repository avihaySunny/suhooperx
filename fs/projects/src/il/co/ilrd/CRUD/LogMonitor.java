package il.co.ilrd.CRUD;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.FileSystems;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.Observable;
import java.util.Observer;


@SuppressWarnings("deprecation")
public class LogMonitor {
	private LogMonitorObserver observed = new LogMonitorObserver(); 
	private File toMonitor ; 
	private boolean monitorOn = true; 
	/*-----------------------------------------------------*/
	public void stopMonitoring() {
		monitorOn = false; 
		toMonitor.setLastModified(System.currentTimeMillis());
	}
	/*-----------------------------------------------------*/
	public void register(Observer obs) {
		observed.registerObserver(obs);
	}
	/*-----------------------------------------------------*/
	public void unregister(Observer obs) {
		observed.unregisterObserver(obs);
	}
	/*-----------------------------------------------------*/
	public LogMonitor(String pathToMonitor) throws IOException {
		toMonitor = new File(pathToMonitor);  
		if (!toMonitor.exists()) {
			throw new IllegalArgumentException(); 
		}
	}
	/*-----------------------------------------------------*/
	public void startMonitoring(){
		
		Runnable watching = new Runnable() {
			@Override
			public void run() {
			try {
				long lastModification; 
				BufferedReader fileReader = new BufferedReader(new InputStreamReader(new FileInputStream(toMonitor)));
				WatchService watcher = FileSystems.getDefault().newWatchService();
				WatchKey key = toMonitor.getParentFile().toPath().register(watcher, StandardWatchEventKinds.ENTRY_MODIFY);
				
				readAllLines(fileReader);
				
				lastModification = toMonitor.lastModified();
				while(monitorOn) {
					 watcher.take(); 
					
					if (lastModification < toMonitor.lastModified()) {	
						lastModification = toMonitor.lastModified(); 
						readAllLines(fileReader);
					}
					
					key.pollEvents(); 
					key.reset();
				}
				
				fileReader.close();
			} catch (Exception e) {e.printStackTrace();}}};
			
			new Thread(watching).start(); 		 
	}
	/*-----------------------------------------------------*/
	private class LogMonitorObserver extends Observable{

		private void registerObserver(Observer obs) {
			addObserver(obs);
		}
		
		private void setAndNotify(String s) {
			setChanged(); 
			notifyObservers(s);
		}
		
		private void unregisterObserver(Observer obs) {
			deleteObserver(obs);
		}
	}
	/*-----------------------------------------------------*/
	private void readAllLines(BufferedReader fileReader) {
		try{
			String s;
			while ((s = fileReader.readLine()) != null) {
				observed.setAndNotify(s);
			}
		}catch (Exception e) {}
	}
	/*---------------------------------------------------------*/
	
}


