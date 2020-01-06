package ClassesForLoader;

public class ClassTestB implements actions{
	int x; 
	
	public void PrintName() {
		System.out.println(this.getClass().toString());
		
	}
	
	public void PrintVal(int val) {
		System.out.println(val);
	}
}
