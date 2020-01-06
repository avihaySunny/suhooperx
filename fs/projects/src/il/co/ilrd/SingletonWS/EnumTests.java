package il.co.ilrd.SingletonWS;

public class EnumTests {
	public static void main(String[] args) {
		
		SingletonWS a = SingletonWS.getInstance();
		SingletonWS b = SingletonWS.getInstance(); 
		if (a == b)
			System.out.println("equals");
		System.out.println(a.toString());
		DoubleCheckLock c = DoubleCheckLock.getInstance();
		System.out.println(c != null);
	}
}
