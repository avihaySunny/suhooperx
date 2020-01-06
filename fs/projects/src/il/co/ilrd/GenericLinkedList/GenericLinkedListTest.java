package il.co.ilrd.GenericLinkedList;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

import org.junit.Test;

public class GenericLinkedListTest {
	
	@Test 
	public void testFindInList()
	{
		int sizeA = 50; 
		GenericLinkedList<Integer> list = new GenericLinkedList<Integer>(); 
		Integer existingVal = new Integer(5);
		Integer nonExistingVal = new Integer(55);
		
		for (int i = 0; i < sizeA; ++i	) {
			list.pushFront(new Integer(i));
		}
		
		assertEquals(existingVal, list.find(existingVal).next());
		assertNull(list.find(nonExistingVal));
	}
	
	@Test 
	public void testReverse() {
		int sizeA = 5000; 
		GenericLinkedList<Integer> list = new GenericLinkedList<Integer>();  
		for (int i = 0; i < sizeA; ++i) {
			list.pushFront(new Integer(i));
		}
			
		GenericLinkedList<Integer> revList = GenericLinkedList.reverse(list);
		for (int i = 0; i < sizeA; ++i) {
			assertEquals(revList.popFront().intValue(), i);
		}
	}
	
	@Test 
	public void testIsEmpty() {
		GenericLinkedList<String> slist= new GenericLinkedList<String>();
		assertTrue(slist.isEmpty());
		slist.pushFront("My next");
		assertFalse(slist.isEmpty());
	}
	
	@Test
	public void testMerge() {
		GenericLinkedList<Double> listA = new GenericLinkedList<>();
		GenericLinkedList<Double> listB = new GenericLinkedList<>();
		Double curr; 
		for (int i = 0; i < 5; ++i) {
			listA.pushFront(new Double(i));
			listB.pushFront(new Double(5 + i));
		}
		
		GenericLinkedList<Double> merged = GenericLinkedList.merge(listA, listB);
		for (int i = 0; i < 5; ++i) {
			curr = listA.popFront();
			assertEquals(curr, merged.find(curr).next());
			curr = listB.popFront(); 
			assertEquals(curr, merged.find(curr).next());
		}
	}
	
	@Test (expected = ConcurrentModificationException.class)
	public void testIter() {
		GenericLinkedList<String> listA = new GenericLinkedList<>();
		listA.pushFront("All");
		listA.pushFront("All");
		Iterator<String> iter = listA.iterator();
		listA.pushFront("All");
		iter.next(); 
	}
	
	static <E> void printList(GenericLinkedList<E> list) {
		
		Iterator<E> iter = list.iterator(); 
		while(iter.hasNext()) {
			System.out.println(iter.next());
		}
	}
	
	
}
