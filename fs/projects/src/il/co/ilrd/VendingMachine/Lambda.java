package il.co.ilrd.VendingMachine;

public class Lambda{
	
	public static void main(String[] args) {
	
		NumericTest plus = (s, t) -> { return s + t; }; 
		
		NumericTest subtract = new NumericTest() {
			
			@Override
			public int operate(int a, int b) {
				return a - b; 
			}
		};
		
		System.out.println(plus.operate(5, 6));
		System.out.println(subtract.operate(5, 6));
		System.out.println(new Lambda().new Multiply().operate(10, 2));
		System.out.println(new Lambda().div(10, 2));
	}
	
	class Multiply implements NumericTest{

		@Override
		public int operate(int a, int b) {
			return a*b; 
		}
	}
	public int div (int a, int b) {
		class result implements NumericTest {
			@Override
			public int operate(int a, int b) {
				return a/b; 
			}
		}
		
		return new result().operate(a, b); 
	}
}
