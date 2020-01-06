package cocurrency;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class ListProducerConsumer {
	public static void main(String[] args) {
		Buffer buff = new Buffer(4); 
		Thread producer1 = new Thread (new Runnable() {
			
			@Override
			public void run() {
				try {
					buff.produce();
				}catch(Exception e) {
					e.printStackTrace();
				}
			
			}
		});
		
		Thread consumer1 = new Thread (new Runnable() {
			
			@Override
			public void run() {
				try {
					buff.consume();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});
		
	Thread producer2 = new Thread (new Runnable() {
			
			@Override
			public void run() {
				try {
					buff.produce();
				}catch(Exception e) {
					e.printStackTrace();
				}
			
			}
		});
		
		Thread consumer2 = new Thread (new Runnable() {
			
			@Override
			public void run() {
				try {
					buff.consume();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});
		
		producer1.start();
		consumer1.start();
		 
	}
}

class Buffer{
	private Queue<Integer> list;; 
	private int size; 
	private Semaphore lock; 
	
	public Buffer(int size) {
		list = new LinkedList<Integer>(); 
		this.size = size; 
		lock = new Semaphore(0);
	}
	
	public void produce() throws InterruptedException {
		int value = 0;
		while(true){
			synchronized (this) {
			
				/*while(list.size() >= size) {
					wait(); 
				}*/
				list.add(value);
				System.out.println("Produced : " + value++);
				lock.release();
				//notify(); 
				//Thread.sleep(2000);
			}
		}
	}
	
	public void consume() throws InterruptedException {
		while(true) {
			synchronized (this) {
				lock.acquire();
				/*while(list.size() == 0) {
					wait();
				}*/
				
				System.out.println("Consume : " + list.poll());
				lock.release();		
				//notify();
			}
			
		}
	}
}