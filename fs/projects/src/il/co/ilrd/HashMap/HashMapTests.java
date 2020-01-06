package il.co.ilrd.HashMap;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import org.junit.Test;

public class HashMapTests{
	
	@Test
	public void testContainsKey() {
		HashMap<Integer, String> map = new HashMap<>(17);
		
		assertTrue(map.isEmpty());
		map.put(10, "a"); 
		map.put(11, "b"); 
		map.put(12, "c"); 
		map.put(13, "d"); 
		map.put(14, "e"); 
		map.put(15, "f");
		
		assertTrue(map.containsKey(10));
		assertTrue(map.containsKey(11));
		assertTrue(map.containsKey(12));
		assertTrue(map.containsKey(13));
		assertTrue(map.containsKey(14));
		assertTrue(map.containsKey(15));
		assertTrue(!map.containsKey(16));
		assertTrue(!map.containsKey(17));
		assertTrue(!map.containsKey(18));
	}
	
	@Test
	public void testGetKey() {
		HashMap<Integer, String> map = new HashMap<>(32);
		map.put(10, "a"); 
		map.put(11, "b"); 
		map.put(12, "c"); 
		map.put(13, "d"); 
		map.put(14, "e"); 
		map.put(15, "f");
		
		assertEquals("a", map.get(10));
		assertEquals("b", map.get(11));
		assertEquals("c", map.get(12));
		assertEquals("d", map.get(13));
		assertEquals("e", map.get(14));
		assertEquals("f", map.get(15));
		
	}
	
	@Test
	public void testContainsValue() {
		HashMap<Integer, String> map = new HashMap<>(32);
		map.put(10, "avi"); 
		map.put(11, "been"); 
		map.put(12, "cat"); 
		map.put(13, "don't"); 
		map.put(14, "eat"); 
		map.put(15, "fish");
		
		assertTrue(map.containsValue("avi"));
		assertTrue(map.containsValue("been"));
		assertTrue(map.containsValue("cat"));
		assertTrue(map.containsValue("don't"));
		assertTrue(map.containsValue("eat"));
		assertTrue(map.containsValue("fish"));
	}
	
	@Test
	public void testRemove() {
		HashMap<Integer, String> map = new HashMap<>(32);
		map.put(10, "avi"); 
		map.put(11, "been"); 
		map.put(12, "cat"); 
		map.put(13, "don't"); 
		map.put(14, "eat"); 
		map.put(15, "fish");
		
		assertTrue(map.containsKey(12));
		assertTrue(map.containsKey(14));
		
		map.remove(12); 
		map.remove(14); 

		assertTrue(!map.containsKey(12));
		assertTrue(!map.containsKey(14));
		
		assertEquals(4, map.size());
	}
	
	@Test
	public void testGetSets() {
		HashMap<Integer, String> map = new HashMap<>(32);
		map.put(10, "avi"); 
		map.put(11, "been"); 
		map.put(12, "cat"); 
		map.put(13, "don't"); 
		map.put(14, "eat"); 
		map.put(15, "fish");
		
		Set<Integer> keySet = map.keySet(); 
		Collection<String> valSet = map.values(); 
		Set<Entry<Integer, String>> entrySet = map.entrySet();
		
		assertEquals(keySet.size(), 6); 
		assertEquals(valSet.size(), 6); 
		assertEquals(entrySet.size(), 6); 
		
		Iterator<Integer> iterK = keySet.iterator(); 
		assertEquals(10, iterK.next().intValue());
		assertEquals(11, iterK.next().intValue());
		assertEquals(12, iterK.next().intValue());
		
		Iterator<String> iterV = valSet.iterator(); 
		assertEquals("avi", iterV.next());
		assertEquals("been", iterV.next());
		assertEquals("cat", iterV.next());
		
		Iterator<Entry<Integer,String>> entryIter = entrySet.iterator();  
		
		assertTrue(entryIter.next().getValue().equals("avi"));
		assertTrue(entryIter.next().getValue().equals("been"));
		assertTrue(entryIter.next().getValue().equals("cat"));
	}
	
	@Test
	public void IteratorTest() {
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(20);
		String [] keys = {"a", "b", "c", "d", "e"};
		int [] vals = {1, 2, 3, 4, 5};
		
		for(int i = 0; i < keys.length; ++i)
		{
			myHash.put(keys[i], vals[i]);
		}
		
		System.out.println("\niteratorTest");
		System.out.println("set: " + myHash.entrySet());
		System.out.println("\nkeys: " + myHash.keySet());
		System.out.println("\nvalues: " + myHash.values());
		
		assertEquals(myHash.size(), 5);
		
	}
	
	@Test
	public void putAllTest() {
		System.out.println("put all test:");
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(2);
		myHash.put("a", 11);
		myHash.put("b", 12);
		myHash.put("c", 13);
		myHash.put("d", 14);
		
		HashMap <String, Integer> putAllMap = new HashMap<String, Integer>();
		putAllMap.put("e", 5);
		putAllMap.put("f", 6);
		
		assertEquals(myHash.size(), 4);
		
		myHash.putAll(putAllMap);
		
		assertEquals(myHash.size(), 6);

		for(Map.Entry<String,Integer> pair : myHash.entrySet())
		{
			System.out.println("key: " + pair.getKey() + ", val: " + pair.getValue());
		}

	}


}

