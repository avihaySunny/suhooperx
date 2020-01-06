package cocurrency;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class BasicExecuter {
	public static void main(String[] args) {
		//BasicTest(); 
		//SingleThreadPoolPractice();
		//ThreadPoolPractice(); 
		ScheduledThreadPoolPractice();
	}
	
	static void BasicTest() {
		ExecutorService executor = Executors.newSingleThreadExecutor();
		Future<Integer> futureResult = executor.submit(()-> {
			System.out.println("Hello World");
			return 10; 
		});
	
		try {
			executor.wait(2000L);
				System.out.println(futureResult.isDone());
				System.out.println(futureResult.get()); 
			} catch (Exception e ) {} 
	
		executor.shutdown();
		System.out.println("It's off? " + executor.isShutdown());	
	}

	static void SingleThreadPoolPractice() {
		ExecutorService executer = Executors.newSingleThreadExecutor(); 
		Callable<String> task1 = ()-> {System.out.println("This"); return "This" ;}; 
		Callable<String> task2 = ()-> {System.out.println("is");return "is" ;}; 
		Callable<String> task3 = ()-> {System.out.println("not");return "not" ;}; 
		Callable<String> task4 = ()-> {System.out.println("really");return "really" ;}; 
		Callable<String> task5 = ()-> {System.out.println("sparta");return "sparta" ;}; 
		
		executer.submit(task1);
		executer.submit(task2);
		executer.submit(task3); 
		executer.submit(task4); 
		executer.submit(task5);	
		
	}
	
	static void ThreadPoolPractice() {
		ExecutorService executer = Executors.newFixedThreadPool(4); 
		Callable<String> task1 = ()-> {System.out.println("This"); return "This" ;}; 
		Callable<String> task2 = ()-> {System.out.println("is");return "is" ;}; 
		Callable<String> task3 = ()-> {System.out.println("not");return "not" ;}; 
		Callable<String> task4 = ()-> {System.out.println("really");return "really" ;}; 
		Callable<String> task5 = ()-> {
			long start = System.currentTimeMillis(); 
			while( System.currentTimeMillis() - start >= 14450000) {
			System.out.println("sparta");} 
			return "sparta" ;}; 
		
		executer.submit(task1);
		executer.submit(task2);
		executer.submit(task3); 
		executer.submit(task4); 
		executer.submit(task5);	
		
		if (!executer.isShutdown()) {
			executer.shutdown();
		}
	}
	
	static void ScheduledThreadPoolPractice() {
		ScheduledExecutorService executer = Executors.newScheduledThreadPool(3); 
		Callable<String> task1 = ()-> {System.out.println("This")   ; return "This"  ;}; 
		Callable<String> task2 = ()-> {System.out.println("is")     ;return "is" 	 ;}; 
		Callable<String> task3 = ()-> {System.out.println("not")    ;return "not" 	 ;}; 
		Callable<String> task4 = ()-> {System.out.println("really") ;return "really" ;}; 
		Callable<String> task5 = ()-> {System.out.println("sparta") ;return "sparta" ;}; 
		
		executer.schedule(task1,2 , TimeUnit.SECONDS); 
		executer.schedule(task2,2 , TimeUnit.SECONDS); 
		executer.schedule(task3,2 , TimeUnit.SECONDS); 
		executer.schedule(task4,2 , TimeUnit.SECONDS); 
		executer.schedule(task5,2 , TimeUnit.SECONDS); 	
		
		/*if (!executer.isShutdown()) {
			executer.shutdown();
		}*/
	}
}


