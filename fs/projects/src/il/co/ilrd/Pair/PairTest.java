package il.co.ilrd.Pair;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

import org.junit.Test;

public class PairTest {


	@Test
	public void testMinMax() {
		Integer[] vals = {1, 2, 3, 4, 157, 6,7 ,8, 9, 10, 11}; 
		String[] names = {"A", "B", "G", "D", "E", "F"};
		
		Pair <Integer, Integer> intVals = Pair.minMax(vals);
		Pair <String, String> namePair = Pair.minMax(names); 
		
		assertEquals(vals[0], intVals.getKey());
		assertEquals(vals[4], intVals.getValue());
		assertEquals(names[0], namePair.getKey());
		assertEquals(names[2], namePair.getValue());
	}
	
	@Test
	public void testSwap(){
		Pair <String, Integer> x = Pair.of("Hello", 42);
		Pair<Integer, String> y = Pair.swap(x);
		
		assertEquals(Integer.class, y.getKey().getClass());
		assertEquals(String.class, y.getValue().getClass());
		assertEquals("Hello", y.getValue());
		assertEquals(new Integer(42), y.getKey());
	}
	@Test
	public void testEquals() {
		Pair <Integer, Float> a = Pair.of(12, (float)4.5); 
		Pair <Integer, Float> c = Pair.of(12, (float)4.5); 
		Pair <Float, Integer> b = Pair.swap(a);
		
		assertNotEquals(a, b);
		assertEquals(a, c);
	}
}

