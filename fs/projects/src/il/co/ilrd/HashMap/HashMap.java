/*
 * Writteb by avihay asraf
 * 2/9/
 */

package il.co.ilrd.HashMap;

import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import il.co.ilrd.Pair.*;
//-------------------------------------------------------------------------------------
public class HashMap <K, V> implements Map<K, V> {
	private int hashVersion; 
	private int size;
	private List<LinkedList<Entry<K,V>>> table;
	private final int capacity;
	
	public HashMap()
	{
		//default constructor capacity 
		this(16);
	}
	
	public HashMap(int capacity)
	{
		this.capacity = capacity;
		table = new ArrayList<LinkedList<Entry<K, V>>>(capacity);
		for (int i = 0; i < capacity; ++i) {
			table.add(new LinkedList<Entry<K,V>>()); 
		}
	}
	/*
	 * resets list 
	 */
	@Override
	public void clear() {
		for (LinkedList<Entry<K, V>> list : table) {
			list.clear();
		}
		size = 0; 
	}
	
	@Override
	public boolean containsKey(Object key) {
		int bucketIndx = key.hashCode() % capacity; 
		LinkedList<Entry<K,V>> list = table.get(bucketIndx); 
		for (Entry<K, V> entry : list) {
			if(entry.getKey().equals(key))
				return true; 
		}
		
		return false; 
	}

	@Override
	public boolean containsValue(Object value) {		
		Iterator<V> iter = new ValueSet().iterator(); 
		V val; 
		while(iter.hasNext()) {
			val = iter.next();
			if (val!= null && val.equals(value)) {return true;} 
		}	 
		return false; 
	}

	@Override
	public V get(Object key) {
		Entry<K, V> currEntry;  
		int bucketIndx = key.hashCode() % capacity; 
		Iterator<Entry<K,V>> iter = table.get(bucketIndx).iterator();
		
		while (iter.hasNext()) {
			currEntry = iter.next();  
			if(currEntry.getKey().equals(key))
				return currEntry.getValue();
				
			}
		return null; 
	}
	
	@Override
	public boolean isEmpty() {
		return size == 0;
	}

	@Override
	public V put(K key, V value) {
		int bucketIndx = key.hashCode() % capacity;
		V oldVal; 
		size++; 
		hashVersion++; 
		
		for (Entry<K,V> currEntry : table.get(bucketIndx)) {
			if(currEntry.getKey().equals(key)) {
				oldVal = currEntry.getValue(); 
				currEntry.setValue(value); 
				return oldVal; 
			}
		}
		
		table.get(bucketIndx).add(Pair.of(key, value));
		return value; 
	}
	
	@Override
	public V remove(Object key) {
		int indx = 0; 
		Entry <K,V> tmpEntry = null; 
		int bucketIndx = key.hashCode() % capacity; 
		Iterator<Entry<K,V>> iter = table.get(bucketIndx).iterator();
		
		while (iter.hasNext()) {
			if(iter.next().getKey().equals(key)) {
				tmpEntry =  table.get(bucketIndx).remove(indx);
				--size; 
				hashVersion++; 
				return tmpEntry.getValue();
			}
			++indx ; 
		}
		return null; 
	}

	@Override
	public int size() {
		return size; 
	}

	@Override
	public Collection<V> values() {
		return new ValueSet(); 
	} 	
	
	@Override
	public void putAll(Map<? extends K, ? extends V> map) {
		for(Map.Entry<? extends K, ? extends V> entry : map.entrySet()) {
			if (entry == null)
				break; 
			put(entry.getKey(), entry.getValue());			 
		}
	}
	
	@Override
	public Set<Entry<K, V>> entrySet() {
		return new EntrySet();  
	}
	
	@Override
	public Set<K> keySet() {
		return new KeySet(); 
	}
//-------------------------------------------------------------------------------------	
	private class EntrySet extends AbstractSet<Entry<K,V>> {
		@Override
		public Iterator<Entry<K,V>> iterator() {
			return new EntrySetIterator();
		}
		
		@Override
		public int size() {
			return size; 
		}
		/*
		 *  might throw Concurrent exception in case of outdated iterator 
		 */
		private class EntrySetIterator implements Iterator<Entry<K,V>> {
			int entrySetVersion; 
			Iterator<LinkedList<Entry<K,V>>> tableIter = table.iterator(); 
			Iterator<Entry<K, V>> pairIter = tableIter.next().iterator(); 
			
			public EntrySetIterator() {
				entrySetVersion = hashVersion;
			}
			@Override
			public boolean hasNext(){
				return (!pairIter.hasNext() && !tableIter.hasNext()) ? false : true;  
			}

			@Override
			public Entry<K,V> next(){
				LinkedList<Entry<K,V>> curList = null;   				
				if(entrySetVersion != hashVersion)
					throw new ConcurrentModificationException(); 
				
 				if(pairIter.hasNext()) {
					return pairIter.next();
				}
				
				while(tableIter.hasNext()) {
					curList = tableIter.next();	
					if (!curList.isEmpty()) {
						pairIter = curList.iterator(); 
						return pairIter.next();
					}
				} 
				
				return null; 
			}	
		}
	}
//-------------------------------------------------------------------------------------	
	private class KeySet extends AbstractSet<K> {
		@Override
		public Iterator<K> iterator() {
			return new KeySetIterator();
		}
		@SuppressWarnings("unused")
		public Iterator<K> iterator(int bucketIndx) {
			return new KeySetIterator(bucketIndx);
		}

		@Override
		public int size() {
			return size;  
		}
		
		private class KeySetIterator implements Iterator<K> {
			Iterator<Entry<K,V>> iter = new EntrySet().iterator(); 
			int keySetVersion = hashVersion; 
			
			public KeySetIterator() {
			}
			
			public KeySetIterator(int bucketIndx) {
				iter = table.get(bucketIndx).iterator();
			}
			@Override
			public boolean hasNext() {
				return iter.hasNext();
			}

			@Override
			public K next() {
				Entry<K, V> tmp;  
				if(keySetVersion != hashVersion)
					throw new ConcurrentModificationException();
				tmp = iter.next();
				return (tmp != null ) ? (tmp.getKey()) : (null); 
			}
		}
	}
//-------------------------------------------------------------------------------------
	private class ValueSet extends AbstractSet<V> {
		
		@Override
		public Iterator<V> iterator() {
			return new ValueSetIterator();
		}

		@Override
		public int size() {
			return size; 
		}
		
		private class ValueSetIterator implements Iterator<V> {
			Iterator <Entry<K,V>> iter = new EntrySet().iterator(); 
			int valueSetVersion = hashVersion; 
			
			@Override
			public boolean hasNext() {
				return iter.hasNext();
			}

			@Override
			public V next() {
				 
				if(valueSetVersion != hashVersion)
					throw new ConcurrentModificationException();
				Entry<K, V> tmp = iter.next();
				return (tmp == null ) ? (null) : (tmp.getValue()); 
			}
		}
	}
}
//-------------------------------------------------------------------------------------
