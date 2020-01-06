public class Box <T> {
	private T var; 
	
	public Box(T ob) {
		var = ob; 
	}
	
	public void set(T ob) {
		var = ob; 
	}
	
	public T get() {
		return var; 
	}
	
	public void showType() {
		System.out.println("type is : " + var.getClass().getName());
	}
}
