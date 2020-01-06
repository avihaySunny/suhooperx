package il.co.ilrd.ThreadPool;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

import org.junit.jupiter.api.Test;

public class ThreadPoolTests {
	
	public static void main(String[] args) throws InterruptedException {
		//testRunResume();
		//testFutureStatus();
		testAwaiting();
		//testThreadsGoingUp();
		//testPauseResume();
	}
	
	
	@Test
	public static void testThreadsGoingUp() {
		ThreadPool threadPool = new ThreadPool(2);
		assertEquals(2, threadPool.getCurrentNumberOfThreads());
		Runnable task1 = new Runnable() {

			@Override
			public void run() {
				try {
					Thread.sleep(4000); 
					System.out.println(Thread.currentThread().getName() + ": Task2.");
				}catch (Exception e) {
				}
			}
			
		};
		
		Runnable task2 = new Runnable() {

			@Override
			public void run() {
				try {
					Thread.sleep(4000); 
					System.out.println(Thread.currentThread().getName() + ": Task2.");
				}catch (Exception e) {
				}
			}
			
		};
		threadPool.setNumOfThreads(4);
		
		threadPool.submit(task1, ThreadPool.Priority.HIGH);
		threadPool.submit(task2, ThreadPool.Priority.HIGH);
		threadPool.submit(task1, ThreadPool.Priority.HIGH);
		threadPool.submit(task2, ThreadPool.Priority.HIGH);	
		
		assertEquals(4, threadPool.getCurrentNumberOfThreads());
	}
	
	@Test
	public static void testPauseResume() {
		ThreadPool threadPool = new ThreadPool(2);
		
		Runnable task1 = new Runnable() {

			@Override
			public void run() {
				try {
					System.out.println("X");
					Thread.sleep(500); 
					System.out.println(Thread.currentThread().getName() + ": Task2.");
				}catch (Exception e) {
				}
			}
			
		};
		
		Runnable task2 = new Runnable() {

			@Override
			public void run() {
				try {
					System.out.println("X");
					Thread.sleep(2000); 
					System.out.println(Thread.currentThread().getName() + ": Task2.");
				}catch (Exception e) {
				}
			}
			
		};
		
		Future<Void> fuValue = threadPool.submit(task1, ThreadPool.Priority.HIGH);
		threadPool.submit(task2, ThreadPool.Priority.HIGH);
		threadPool.pause();
		assertEquals(false, fuValue.isDone());
		threadPool.submit(task1, ThreadPool.Priority.HIGH);
		threadPool.submit(task2, ThreadPool.Priority.HIGH);	
		threadPool.resume();
	}
	
	public static void testRunResume() {
		ThreadPool threadPool = new ThreadPool(2);
		
		threadPool.submit(()->{System.out.println("X");}, ThreadPool.Priority.MEDIUM );
		threadPool.submit(()->{System.out.println("s");}, ThreadPool.Priority.MEDIUM );
		threadPool.pause();
		threadPool.submit(()->{System.out.println("X");}, ThreadPool.Priority.MEDIUM );
		threadPool.submit(()->{System.out.println("X");}, ThreadPool.Priority.MEDIUM );
		threadPool.resume();
		threadPool.submit(()->{System.out.println("X");}, ThreadPool.Priority.MEDIUM );
		threadPool.submit(()->{System.out.println("X");}, ThreadPool.Priority.MEDIUM );
		threadPool.pause();
		threadPool.submit(()->{System.out.println("X");}, ThreadPool.Priority.MEDIUM );
		threadPool.submit(()->{System.out.println("X");}, ThreadPool.Priority.MEDIUM );
		threadPool.resume();
		threadPool.shutdown();

	}
	
	public static void testFutureStatus() {
		ThreadPool threadPool = new ThreadPool(2); 
		int err = 0; 

		threadPool.pause();
		
		Future<Integer> val = threadPool.submit(()->{
			return 4; 
			} 
			, ThreadPool.Priority.MEDIUM );
		
		Future<Integer> val1 = threadPool.submit(()->{
			return 4; 
			} 
			, ThreadPool.Priority.MEDIUM );
		
		Future<Integer> val2 = threadPool.submit(()->{
			return 4; 
			} 
			, ThreadPool.Priority.MEDIUM );
		
		Future<Integer> val3 = threadPool.submit(()->{
			Thread.currentThread().wait(2000);
			return 4; 
			} 
			, ThreadPool.Priority.MEDIUM );
	
		
		if(val.isDone()) {
			++err;
		}
		if(val1.isDone()) {
			++err;
		}
		if(val2.isDone()) {
			++err;
		}
		if(val3.isDone()) {
			++err;
		}
		
		val.cancel(true);
		val1.cancel(true);
		val2.cancel(true);
		val3.cancel(true);
		
		threadPool.resume();
		
		if(val.isDone()) 
			++err;
		
		if(val1.isDone()) 
			++err;
		
		if(val2.isDone()) 
			++err;
		
		if(val3.isDone()) 
			++err;
		//-----------------------------------
		if(!val1.isCancelled()) {
			++err;
		}
		//-----------------------------------
		threadPool.shutdown();
		
		if(err != 0)
			System.out.println("cancel test failed");

	}
	
	public static void testAwaiting() {
		ThreadPool threadPool = new ThreadPool(3); 
		
		threadPool.execute(()->{while(true);}); 
		threadPool.submit(()->{while(true);});
		threadPool.submit(()->{while(true);});
		
		
		threadPool.setNumOfThreads(6);
		threadPool.submit(()->{System.out.println("X"); Thread.sleep(1000); return null; });
		threadPool.submit(()->{System.out.println("Y"); Thread.sleep(1000); return null; });
		threadPool.submit(()->{System.out.println("Z"); Thread.sleep(1000); return null; });
		
		threadPool.shutdown();
		
		if(!threadPool.awaitTermination(2, TimeUnit.SECONDS)) {
			System.out.println("THREADS STUCK");
		}

	}
		
}
