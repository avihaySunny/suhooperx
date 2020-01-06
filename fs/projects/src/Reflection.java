import java.lang.reflect.*;
import java.lang.Class.*;

import il.co.ilrd.Complex.Complex;
import il.co.ilrd.VendingMachine.Display;

public class Reflection implements Display{
	@Override
	public void printToDisplay(String toPrint) {
		// TODO Auto-generated method stub
		System.out.println("Hello");
	}
	public static void main(String[] args) {
		Complex z = new Complex(2,2);
		Class c = z.getClass();
			Field[] fields;
			Method[] methods = null;  
			Constructor<Complex> a; 
			try {
				fields = Complex.class.getDeclaredFields();
				methods = Complex.class.getDeclaredMethods();
				a = Complex.class.getDeclaredConstructor(double.class, double.class);
				System.out.println(a.newInstance(5, 5).toString());
				System.out.println(methods[0].invoke(z, null));
				System.out.println(c.getInterfaces()[0].toString());
				
				
			}catch (Exception e) {System.out.println(e.getMessage());}
		System.out.println(c.getSuperclass());
	}
}