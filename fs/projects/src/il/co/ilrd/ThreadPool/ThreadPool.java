/*
 * written by Avihay Asraf
 * ThreadPool implemntation 
 * 16.9.2019
 */

package il.co.ilrd.ThreadPool;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import il.co.ilrd.WaitableQueue.WaitableQueue;


public class ThreadPool implements Executor{
	private WaitableQueue<Task<?>> tasksQueue = new WaitableQueue<>(Task::compareTo); 
	private int threadCount; 
	private boolean off = false; 
	private boolean pause = false; 
	private Semaphore semPause = new Semaphore(0); 
	private static final int MAX_PRIORITY = Priority.HIGH.priority + 1; 
	private static final int MIN_PRIORITY = Priority.LOW.priority - 1; 
	
	public ThreadPool(int threadCount){
		this.threadCount = threadCount;  
 		addThreads(threadCount, true);
	
	}
/*--------------------------------------------------------------------------------------------------------------*/
	public enum Priority {
		LOW(1), MEDIUM(5), HIGH(10);
	 
		private int priority; 

		private Priority(int priority){ 
			this.priority = priority; 
		}
		
		private int getPriority() {
			return priority; 
		}
	}
/*--------------------------------------------------------------------------------------------------------------*/	
	private class ThreadPoolManager extends Thread {
		private boolean toRun = true; 

		@Override
		public void run() {
			while (toRun){
				try {
					tasksQueue.dequeue().run();
				}catch (Exception e) {}
			}
		}
	}
/*--------------------------------------------------------------------------------------------------------------*/	
	public Future<Void> submit(Runnable action, Priority p){ 	
			return submit(Executors.callable(action, null), p);
	}
	
	public <T> Future<T> submit(Runnable action, Priority p, T v){
			return submit(Executors.callable(action, v), p); 
	}
	
	public <T> Future<T> submit(Callable<T> call){
			return submit(call, Priority.MEDIUM); 
	}

	public <T> Future<T> submit(Callable<T> c, Priority p){
		if (off) {
			throw new UnsupportedOperationException(); 
		}
		Task<T> task = new Task<T>(c,p.getPriority());
		try {
			tasksQueue.enqueue(task); 
			return task.future ; 
		}catch(Exception e) {} 
		
		return null; 
	}
	
	private <T> void submitSysTask(Callable<T> c, int priority){
		try {
			tasksQueue.enqueue(new Task<>(c, priority)); 
		} catch (Exception e) {}
	}
/*--------------------------------------------------------------------------------------------------------------*/	
	@Override
	public void execute(Runnable arg0) {
		submit(Executors.callable(arg0), Priority.MEDIUM); 
	}
/*--------------------------------------------------------------------------------------------------------------*/	
	public void setNumOfThreads (int threadCount){
		if (threadCount < 0) {
			throw new IllegalArgumentException(); 
		}
		
		if (this.threadCount <= threadCount) {
			if (pause) {pauseThreads(threadCount - this.threadCount);}
			addThreads(threadCount - this.threadCount, !semPause.hasQueuedThreads()); 
		}
		else { 
			shutdownThreads(this.threadCount - threadCount); 
		}
		
		this.threadCount = threadCount; 
	}
/*--------------------------------------------------------------------------------------------------------------*/	
	private void addThreads(int toAdd, boolean start){
		
		for (int i = 0; i < toAdd; ++i) {
			Thread t = new ThreadPoolManager();			
			t.start();
		}
	}
/*--------------------------------------------------------------------------------------------------------------*/	
	private void pauseThreads(int toStop) {
		pause = true; 
		for (int i = 0; i < toStop; ++i) {
			submitSysTask(()->{semPause.acquire(); return null;}, MAX_PRIORITY);  
		}
	}
/*--------------------------------------------------------------------------------------------------------------*/
	public void pause() {
		pauseThreads(threadCount);
	}
/*--------------------------------------------------------------------------------------------------------------*/	
	public void resume() {
		pause = false; 
		semPause.release(threadCount);
	}
/*--------------------------------------------------------------------------------------------------------------*/	
	public int getCurrentNumberOfThreads(){
		return threadCount; 
	}
/*--------------------------------------------------------------------------------------------------------------*/
	private void shutdownThreads(int threadNumToShut) {
		for (int i = 0; i < threadNumToShut; ++i) {
			submitSysTask(()-> {
				((ThreadPoolManager)Thread.currentThread()).toRun = false;
				return null; } ,MIN_PRIORITY);
		}
	}
/*--------------------------------------------------------------------------------------------------------------*/
	public void shutdown() {
	  	if (!semPause.hasQueuedThreads()) {resume();}
		off = true; 
		shutdownThreads(threadCount);
	}
/*--------------------------------------------------------------------------------------------------------------*/
	public boolean awaitTermination(long timeout, TimeUnit unit){
		try {
			wait(unit.convert(timeout, unit)); 
		}catch (Exception e) {}
		
		return tasksQueue.isEmpty(); 
	}
/*--------------------------------------------------------------------------------------------------------------*/	
	private static class Task<T>  implements Comparable<Task<?>>, Runnable{
		private int taskPriority; 
		private Callable<T> call; 
		private TaskFuture future = new TaskFuture(); 
		 
		private States state = States.WAITING; 
		private T result;
		
		private enum States {
			RUNNING, 
			WAITING, 
			COMPLETED, 
			CANCLED; 
		}; 
		
		public Task(Callable<T> c, int  priority) {
			taskPriority = priority; 
			call = c; 
		}
		
		@Override
		public void run() {
			try {
				state = States.RUNNING; 
				result = call.call(); 
				future.taskSem.release();
				state = States.COMPLETED; 
			}
			catch (Exception e){}			
		}

		@Override
		public int compareTo(Task<?> arg0) {
			return arg0.taskPriority  - this.taskPriority ;   
		}
	
		private class TaskFuture implements Future<T> {
			private Semaphore taskSem = new Semaphore(0);
			
			@Override
			public boolean cancel(boolean mayInterruptIfRunning) {
				call = ()->{return null; }; 
				if (state == States.RUNNING  || state == States.COMPLETED) {
					return false; 
				}
				
				state = States.CANCLED; 
				return true; 
			}
			
			@Override
			public boolean isCancelled() {
				return state == States.CANCLED; 
			}

			@Override
			public boolean isDone() {
				return state == States.COMPLETED; 
			}

			@Override
			public T get() throws InterruptedException, ExecutionException {
				if(state == States.CANCLED ) {
					throw new UnsupportedOperationException(); 
				}
				taskSem.acquire(); 
				return result; 
			}

			@Override
			public T get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
				if(state == States.CANCLED ) {
					throw new UnsupportedOperationException(); 
				}
				if (taskSem.tryAcquire(timeout, unit)) {
					return result; 
				}	
				return null;
			}	
		}
	}
	
/*--------------------------------------------------------------------------------------------------------------*/

}

