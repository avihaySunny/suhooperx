package il.co.ilrd.Complex;

import java.util.Arrays;

public class ComplexTests {
	public static void main(String[] args) {
		Complex z = new Complex(5, 5);
		
		var z1 = new Complex(4,4); 
		Comparable<Complex> s = z1; 
		
		System.out.println(s.compareTo(new Complex(5, 5)));
		
		/*int faileTests = 0; 
		
		if (!testAdd()){
			++faileTests;
			System.out.println("Add test failed");
		}
		if (!testSub()){
			++faileTests; 
			System.out.println("Subtract test has failed");
		}
		if (!testCompare()){
			++faileTests;
			System.out.println("Compare test has failed");
		}
		if (!testEquals()){
			System.out.println("Equals test has failed");
			++faileTests;
		}
		if(!testStringToComplex()) {
			++faileTests;
			System.out.println("String To Complex failed");
		}
		
		if(!testCompareWithSort()) {
			++faileTests;
			System.out.println("Compare sort test has failed");
		}
		
		if(!testPhase()) {
			++faileTests;
			System.out.println("Phase Test has failed");
		}
	
		if (faileTests == 0) 
			System.out.println("All Tests Successfull"); */
			
	}
	
	static boolean testAdd() {
		Complex z1 = new Complex(1, 1); 
		Complex z2 = new Complex(-1, -1); 
		
		return z1.add(z2).equals(new Complex(0, 0));
	}
	
	static boolean testSub() {
		Complex z1 = new Complex(1, 1); 
		Complex z2 = new Complex(1, 1); 
		
		return z1.sub(z2).equals(new Complex(0, 0));
	}
	
	static boolean testCompare() {
		Complex z1 = new Complex(1, 1); 
		Complex z2 = new Complex(1, 1);
		Complex z3 = new Complex(3, 4); 
		Complex z4 = new Complex(4, 3);
		
		if (z1.compareTo(z2) != 0) return false; 
		if (z3.compareTo(z4) != 0) return false; 
		if (z2.compareTo(z4) > 0) return false; 
		
		return true; 
	}
	
	static boolean testEquals() {
		Complex z1 = new Complex(1, 1); 
		Complex z2 = new Complex(1, 1);
		Complex z3 = new Complex(3, 4); 
		
		return (z1.equals(z2) == true && z1.equals(z3) == false); 
	}
	
	static boolean testStringToComplex() {
		Complex z1 = new Complex (-5.6, -4.1); 
		Complex z2 = new Complex(-2, -4); 
		
		try 
		{
			return z1.equals(Complex.stringToComplex("-5.6 - 4.1i")) && 
					!z2.equals(Complex.stringToComplex("-5.6 -4.1i"));
		}
		catch(Exception e) {
			System.out.println(e.getMessage());
			return false; 
		}
	}
	
	static boolean testCompareWithSort() {
		
		try
		{
			Complex[] numArr = {Complex.stringToComplex("1 + 2i"),
		
							Complex.stringToComplex("- 1 + 4i"),
							Complex.stringToComplex("-6 +2i"),
							Complex.stringToComplex("-3.5 + 1.16i"),
							Complex.stringToComplex("-15.6 - 4i"),
							Complex.stringToComplex("12.6 - 5i")};
			
			Arrays.sort(numArr); 
			for(int i = 1; i < numArr.length ; ++i){
				if (numArr[i-1].norm() > numArr[i].norm())
					return false;
				}
			return true; 
		}
		catch (Exception e) {
			System.out.println(e.getMessage());
			return false;
		}
		
	}
		
	static boolean testPhase() {
		if (45 != Math.toDegrees(new Complex(1, 1).phase())) {
			return false; 
		}
		
		if (90 != Math.toDegrees(new Complex(0, 1).phase())) {
			return false;
		}
		
		return true; 
	}
}
