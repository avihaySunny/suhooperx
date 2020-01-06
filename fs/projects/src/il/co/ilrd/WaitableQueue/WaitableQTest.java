package il.co.ilrd.WaitableQueue;

import java.util.Random;
import java.util.concurrent.TimeUnit;

public class WaitableQTest {
	public static void main(String[] args) {
		WaitableQueue<Integer> myQ = new WaitableQueue<>(Integer::compareTo); 
	
		Runnable runMethForConsumer = new Runnable() {
			@Override
			public void run() {
				while(true) {
					try {
						System.out.println(myQ.dequeue());	
					}catch (InterruptedException e) {
						e.printStackTrace();
					}		
				}
			}
		};
		
		Runnable consumerDelay = new Runnable() {
			@Override
			public void run() {
				while(true) {
					try {
						System.out.println(myQ.dequeue(2, TimeUnit.SECONDS));	
					}catch (Exception e) {
						e.printStackTrace();
					}		
				}
			}
		};
		
		Thread producerForQ = new Thread(new Runnable() {
			@Override
			public void run() {
				/*Integer[] letterList = {"e", "b", "c","d","e","f", "G"};  
				int i = 0;*/
				Random ranGen = new Random(); 
				while(true) {
					try {
							myQ.enqueue(ranGen.nextInt(100)); 
						//	++i; 
							
						} catch (InterruptedException e) {
							e.printStackTrace();
				}
			
				}
			}
		});
		
		Thread remover = new Thread(new Runnable() {
			
			@Override
			public void run() {
				Random ranGen = new Random();
				try {
					myQ.remove(ranGen.nextInt());
					System.out.println("value has been removed");
					wait(1000L); 
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
			}
		}); 
	
			
		Thread consumer1 = new Thread(runMethForConsumer);
		Thread consumer2 = new Thread(runMethForConsumer);
		Thread consumerDelayed = new Thread (consumerDelay); 
		producerForQ.start();
		
		remover.start();
		consumer1.start();
		consumer2.start();
	
		consumerDelayed.start();
		consumer2.notify();
		
		
		
	
	}
}
