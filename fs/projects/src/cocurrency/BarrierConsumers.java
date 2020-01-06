package cocurrency;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BarrierConsumers {
	StringBuffer message; 
	int threadCount = 3; 
	WordConsumer listner1 = new WordConsumer(message); 
	WordConsumer listner2 = new WordConsumer(message); 
	WordConsumer listner3 = new WordConsumer(message); 
	
	wordProducer a = new wordProducer(message); 
	Thread tp1 = new Thread(a); 
	Thread cp1 = new Thread(listner1);
	Thread cp2 = new Thread(listner2);
	Thread cp3 = new Thread(listner3);
	
	
	Lock mylock = new ReentrantLock(); 
	Condition cond = mylock.newCondition();
	Semaphore sem = new Semaphore(0); 
 	
	public static void main(String[] args) {
		BarrierConsumers ob = new BarrierConsumers(); 
		
		ob.tp1.start();
		
	}

	
	class wordProducer extends Thread{
		StringBuffer message; 

		public wordProducer(StringBuffer message) {
			this.message = message; 
		}
		
		@Override
		public void run() {
			cp2.start();
			cp3.start();
			cp1.start();
			
			while(true) {
				mylock.lock();
				message.append('a');
				System.out.println(message);
				sem.drainPermits(); 
				mylock.unlock();
				cond.signalAll();	
			}
		}
	}

	class WordConsumer extends Thread{
		StringBuffer message; 

		public WordConsumer(StringBuffer message) {
			this.message = message; 
		}

		@Override
		public void run() {
			mylock.lock(); 
			System.out.println(message);
			sem.release();
			try {
				cond.await(); 
			}catch(InterruptedException e) {}
			finally {
				mylock.unlock();
				
			}
			
		}
	}
}







