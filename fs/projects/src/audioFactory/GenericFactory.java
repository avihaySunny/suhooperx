package audioFactory;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class GenericFactory <T, K, A> {
	private Map <K, Function<A,? extends T>> classMap; 
	public GenericFactory() {
		classMap = new HashMap<K, Function<A,? extends T>>();
	}
	public void addClass(K key, Function< A,? extends T> entry) {
		 classMap.put(key, entry); 
	}
	
	public T create(K classKey, A args) {
		return classMap.get(classKey).apply(args);
	}

}


	
