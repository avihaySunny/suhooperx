
//import java.io.BufferedReader;
import java.io.File;
//import java.io.File;
import java.io.IOException;


public class foo{
	File fp; 
	public foo() {}
	
	public void function1() throws IOException{
		System.out.println("x");
	}
	
	public void func2(Integer x) {
		if (x == null)
			throw new NullPointerException("Null");  
	}
	public static void main(String[] args) {
		foo a = new foo(); 
		Integer x = null;
		a.fp = new File("~git/");
		
		try{
			a.function1();
			System.out.println("working ");
		}catch (Exception e) {
			System.out.println("shit");
		}
		
		a.func2(x);
	}

}
