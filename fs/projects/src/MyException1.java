
public class MyException1 extends RuntimeException {
	
	private static final long serialVersionUID = 1L;
	int a; 
	public void imAThrowes ()  {
		System.out.println("Im about to throw up\n");
		throw new RuntimeException("this is exception!\n");
	}
	
	public static void main(String[] args) {
		MyException1 a = new MyException1(); 
		try {

			a.imAThrowes();
			
		} catch (Exception e) {
			System.err.println(e.getMessage());
		}
		
	}

}
