package ClassesForLoader;

public class ClassTestA implements actions {
	int x; 
	
	public void PrintName() {
		System.out.println(this.getClass().toString());
		
	}
	
	public void PrintVal(int val) {
		System.out.println(val);
	}
}
