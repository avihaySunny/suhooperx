package il.co.ilrd.Observer;

import java.util.function.Consumer;

public abstract class BroadcastManager <T extends Consumer<E>, E>{
	Subject<T, E> sub; 
	
	public BroadcastManager() {
		sub = new Subject<>();
	}
	public void start(Consumer<E> c){
		sub.register(c);
	}
	
	public void stop() {
		
	}
	
	public void broadcastAll(E event) {
		sub.broadcast(event);
	}
	
	
}
