import java.util.List;

public class Generica {
	@SuppressWarnings("rawtypes") 
	public static void main(String[] args) {
		Integer[] ints = {1, 6, 8, 12, 15, 241}; 
		Double[] doubles = {1.5, 2.4 , 3.5}; 
		Character[] cs = {'a', 'b', 'c'};
		List<Object> l1; 
		List <Integer> l2; 
		
		Box<Integer> var = new Box<Integer>(55); 
		Box<String> namey = new Box<>("HELLO");
		
		//using raw type (i didnt use any types) 
		Box b = new Box(new Double(96.2));
		
		double d = (Double)b.get();
		System.out.println("my d is : " + d);
		int number = var.get(); 
		System.out.println("will you be my: " + number);
		var.showType();
		System.out.println(namey.get());
		namey.showType();
		
		DoubleBox<Integer, String> x = new DoubleBox<>(5, "Hey"); 
		System.out.println(x.getT());
		System.out.println(x.getV());
		x.showType();
		
		printArray(ints);
		printArray(doubles);
		printArray(cs);
	}

	public static <E> void printArray(E[] array) {
		for (E elemnent : array) {
			System.out.println(elemnent); 
		}
	}
}
