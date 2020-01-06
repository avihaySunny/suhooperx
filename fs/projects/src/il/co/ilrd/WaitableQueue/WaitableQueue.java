package il.co.ilrd.WaitableQueue;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;

public class WaitableQueue<T> {
	private PriorityQueue<T> pq;
	private Semaphore dqLock;
	private ReentrantLock lock; 
	
	
	public WaitableQueue (Comparator<T> c){	
		pq = new PriorityQueue<>(c); 
		dqLock = new Semaphore(0);
		lock = new ReentrantLock(); 
		
	}
	
	public boolean enqueue(T data) throws InterruptedException{
		lock.lock(); 
		boolean result = pq.add(data); 
		lock.unlock();
		dqLock.release();
		
		return result; 
	}
	
	public boolean isEmpty() {
		return pq.isEmpty(); 
	}
	public T dequeue() throws InterruptedException{
		dqLock.acquire(); 
		lock.lock();
		T data = pq.remove(); 
		lock.unlock(); 	
		
		return data;
	}
	
	public T dequeue(long timeout, TimeUnit unitOfMeasure){
		T data = null; 
		try {
			dqLock.tryAcquire(timeout, unitOfMeasure); 
			lock.lock();
			data = pq.remove(); 

		}catch(InterruptedException e) {}
		finally {
			lock.unlock(); 
			}
		return data;
	}
	
	public boolean remove(T data)  {
		
		lock.lock(); 
		boolean result = pq.remove(data); 
		if (result) {
		try{
			dqLock.acquire(); 
		}catch(Exception e) {}
		
		finally {
			lock.unlock(); 	
			}
		}
		else 
			lock.unlock();
		return result; 
	}
	
}
