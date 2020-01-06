package cocurrency;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class SpecialBarrier {
	private int userCount; 
	private Semaphore slock = new Semaphore(0); 
	private AtomicInteger currentHolding = new AtomicInteger(0); 
	
	public SpecialBarrier(int userCount) {
		this.userCount = userCount; 
	}
	public void lock() {
		currentHolding.incrementAndGet();
		if (currentHolding.compareAndSet(userCount, 0)) {
			slock.release(userCount);
		}
		try {
			slock.acquire();
		} catch (InterruptedException e) {}
	}
	
	
	public static void main(String[] args) {
		SpecialBarrier sb = new SpecialBarrier(3); 
		Thread a = new Thread(()->{
			while(true) {
				sb.lock();
				System.out.println("A");
			}
		
		}); 
		
		Thread b = new Thread(()->{
			while(true) {
				sb.lock();
				System.out.println("B");
			}
		
		}); 
		
		Thread c = new Thread(()->{
			while(true) {

				sb.lock();
				System.out.println("C");
			}
		
		}); 
		try {
			a.start();
			System.out.println("wait a");
			Thread.sleep(1000L);
			b.start();
			Thread.sleep(1000L);
			System.out.println("wait b");
			c.start();
			System.out.println("wait c");
			
		}catch (Exception e) {
			// TODO: handle exception
		}
		
		
	}
}