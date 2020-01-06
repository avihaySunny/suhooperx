package cocurrency;

import java.util.concurrent.Semaphore;

public class PingPong {
	
	public static void main(String[] args) {
		Semaphore pingLock = new Semaphore(1);
		Semaphore pongLock = new Semaphore(0); 
		Ping ping = new Ping(pingLock, pongLock);  
		Pong pong = new Pong(pingLock, pongLock); 	 
		
		Thread tPong = new Thread(pong); 
		Thread tPing = new Thread(ping); 
		
		tPing.start();
		tPong.start();
	}
	
	
	
}

class Ping extends Thread{
	Semaphore pingLock;
	Semaphore pongLock; 
	
	public Ping(Semaphore pingLock, Semaphore pongLock) {
		this.pingLock = pingLock; 
		this.pongLock = pongLock; 
	}
	
	@Override
	public void run() {
		while(true){
			try {
				pingLock.acquire();
				System.out.println("Ping");
				pongLock.release();
			}catch (InterruptedException e) {}
			
			
		}
	}
}

class Pong extends Thread{
	Semaphore pingLock;
	Semaphore pongLock; 
	
	public Pong(Semaphore pingLock, Semaphore pongLock) {
		this.pingLock = pingLock; 
		this.pongLock = pongLock; 
	}
	
	@Override
	public void run() {
		while(true){
			try {
				pongLock.acquire();
				System.out.println("Pong");
				pingLock.release();
			}catch (InterruptedException e) {}
		}
	}
}