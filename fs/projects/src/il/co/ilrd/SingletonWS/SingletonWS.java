package il.co.ilrd.SingletonWS;

public class SingletonWS {
	private final static SingletonWS instance; 
	private int length; 
	private String name; 
	
	static { 
		instance = new SingletonWS();
		instance.length = 5; 
		instance.name = "Orange";
	}
	
	private SingletonWS(){};
	
	public static SingletonWS getInstance() {return instance;} 
	
	public String toString() {
		return this.length + " " + this.name;  
	}
}
