public class DoubleBox <T, V> {
	private T tob; 
	private V vob; 
	
	public DoubleBox (T ob1, V ob2){
		tob = ob1; 
		vob = ob2; 
	}

	public void setPair(T t, V v) {
		tob = t; 
		vob = v; 
	}
	
	public void showType() {
		System.out.println("type is : " + tob.getClass().getName());
		System.out.println("type is : " + vob.getClass().getName());
	}
	
	public T getT() {
		return tob; 
	}
	
	public V getV() {
		return vob; 
	}
}
