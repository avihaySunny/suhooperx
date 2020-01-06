package il.co.ilrd.Pair;

import java.util.Comparator;
import java.util.Map;

public class Pair <K, V> implements Map.Entry<K, V>{
	private K key;
	private V value;
		
	private Pair(K key, V value){
		this.key = key; 
		this.value = value; 	
	}
	
	public static <K, V> Pair<K, V> of(K key, V value){
		return new Pair<K, V>(key, value);
	}
	
	public static <K, V> Pair<V, K> swap(Pair<K, V> pair){
		return new Pair<V, K>(pair.value, pair.key); 
	}
	
	public static <T extends Comparable <? super T>> Pair<T, T> minMax(T[] elements){
	
		Comparator <T> c = new Comparator<T>() {
			@Override
			public int compare(T o1, T o2) {
				return o1.compareTo(o2);
			}
		};
		
		return minMax(elements ,c::compare); 
	}
	
	public static <T> Pair<T, T> minMax(T[] elements, Comparator <T> c){
		T curr_min; 
		T curr_max;
		T min = elements[0]; 
		T max = elements[0]; 
		 
		for (int i = elements.length%2; i < elements.length; i+=2) {
			if(c.compare(elements[i], elements[i+1]) <= 0){
				curr_min = elements[i]; 
				curr_max = elements[i + 1]; 
			}
			else {
				curr_min = elements[i + 1]; 
				curr_max = elements[i ]; 
			}
			if (c.compare(min ,curr_min) > 0) {
				min = curr_min; 
			}
			
			if (c.compare(max, curr_max) < 0) {
				max = curr_max; 
			}
		}	
		return new Pair <T, T>(min, max);  
	}
	
	@Override
	public K getKey() {
		return key; 
	}
	
	public K setKey(K newKey){
		K oldKey = key;
		key = newKey; 
		return oldKey;
	}

	@Override
	public V getValue() {
		return value; 
	}

	@Override
	public V setValue(V newValue) {
		V oldVal = value; 
		value = newValue; 
		return oldVal;
	}

	@Override
	public String toString() {
		return key.toString() +" & "+ value.toString(); 
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((key == null) ? 0 : key.hashCode());
		result = prime * result + ((value == null) ? 0 : value.hashCode());
		return result;
	}
	
	@SuppressWarnings("unchecked")
	@Override
	public boolean equals(Object obj) {
		if (this == obj) {return true;}
		
		if(obj.getClass().isInstance(this))
		return ((this.key.equals(((Pair<K, V>)obj).key)) 
				&& this.value.equals(((Pair<K, V>)obj).value)) ? 
			true : false ;
		return false;
	}
}