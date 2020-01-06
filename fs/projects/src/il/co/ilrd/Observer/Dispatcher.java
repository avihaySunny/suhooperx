package il.co.ilrd.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class Dispatcher <T>  
{
	private List<Callback<T>> callbackList = new ArrayList<>();
	
	public void broadcast(T event)
	{
		for (Callback<T> c : callbackList) {
			c.update.accept(event);
		}
	}	
	
	public void register(Callback<T> observer)
	{
		callbackList.add(observer); 
		observer.dispatcher = this; 
	}
	
    public void unregister(Callback<T> observer)
    {
    	callbackList.remove(observer);
    }    
   
    public void stopService()
    { 
    	for (Callback<T> c : callbackList) {
    		c.endOfService.run();
    	}
    	
    	callbackList.clear();
    }	
    
   
	static public class Callback <T>
	{
		private Dispatcher <T> dispatcher;
		private final Runnable endOfService;
		private final Consumer<T> update; 
		
		public Callback(Runnable endOfServiceRef, Consumer<T> updateRef)
		{	
			endOfService = (endOfServiceRef == null) ? ()->{;} : endOfServiceRef; 
			update= updateRef;
		}
		
		void stop() {
			dispatcher.unregister(this);
		}
	}

}



