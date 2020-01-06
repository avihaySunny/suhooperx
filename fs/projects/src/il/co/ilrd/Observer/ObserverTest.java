package il.co.ilrd.Observer;

import java.util.function.Consumer;

import il.co.ilrd.Observer.Dispatcher.Callback;

public class ObserverTest {

	public static void main(String[] args) {
		Dispatcher<String> colorRed = new Dispatcher<String>(); 
		Runnable endof = ()-> System.out.println("EndMe");
		Consumer<String> c = (t) -> System.out.println("show me " + t);
		Callback<String> msgMe = new Callback<String>(endof, c);
		
		Runnable two = ()-> System.out.println("hello");
		Consumer<String> c1 = (t) -> System.out.println("do this " + t);
		Callback<String> msgme2 = new Callback<String>(two, c1); 
		
		colorRed.register(msgme2);
		colorRed.register(msgMe);
		
		colorRed.broadcast("hi");
		colorRed.stopService(); 
	}
}
