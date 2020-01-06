package cocurrency;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class Count implements Runnable{
	int counter; 
	ReentrantLock mylock = new ReentrantLock(); 
	//private /*volatile*/ AtomicInteger counter = new AtomicInteger(0);
	
	//atomic counter
	/*@Override
	public void run() {
		while (counter.intValue() < 15000) {
	
			System.out.println(counter);
			counter.getAndIncrement();
		}
	}*/

	@Override
	public void run() {
		
		while (counter < 100000000) {
			System.out.println(counter);
			mylock.lock();
			++counter; 
			mylock.unlock();
		}
		
	}

	public static void main(String[] args) {
		Count chocola = new Count(); 
		Thread t1 = new Thread(chocola); 
		Thread t2 = new Thread(chocola); 
	
		
		t1.start();
		t2.start();
		
	}
	
	
}
