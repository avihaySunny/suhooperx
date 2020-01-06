package il.co.ilrd.LinkedList;

public class LinkedListTest {
	public static void main(String[] args) {
		int testNum = 5; 
		int failedTestsNum = 0 ; 
		
		if (!testIsEmpty())
		{
			++failedTestsNum;
			System.out.println("Is Empty test has failed");
		}
		
		if (!testPushFront())
		{
			++failedTestsNum;
			System.out.println("Push front test has failed");
		}
		
		if (!testSize())
		{
			++failedTestsNum;
			System.out.println("Size test has failed");
		}
		
		if (!testIterators())
		{
			++failedTestsNum;
			System.out.println("Iterators test has failed");
		}
		
		if (!testFindInList())
		{
			++failedTestsNum;
			System.out.println("Find Test has failed");
		}
		
		System.out.println("Number of tests: " + testNum);
		System.out.println("Num of failed tests : " + failedTestsNum);
	}
	
	static boolean testIsEmpty()
	{
		LinkedList list = new LinkedList(); 
		LinkedList initilizedList = new LinkedList(new Integer(5)); 
		
		if (list.isEmpty() != true || initilizedList.isEmpty() != false)
			return false; 
		return true; 
	}

	static boolean testPushFront()
	{
		int max_inserts = 1000; 
		LinkedList list = new LinkedList(); 
		for (int i = 0; i  < max_inserts; ++i) {
			list.pushFront(new Integer(i));
		}
		
		return list.size() == max_inserts; 
	}

	static boolean testSize(){
		LinkedList list = new LinkedList(); 
		int size = 0; 
		int sizeA = 55; 
		
		for (int i = 0; i < sizeA; ++i) {
			list.pushFront(new Integer(i));
		}
		
		if (list.size() != sizeA){
			return false; 
		}
		
		size = list.size();
		
		for (int i = 0; i < size; ++i){
			list.popFront();
		}
		
		return ((list.isEmpty()) ? true : false );  
	}
	
	static boolean testIterators() {
		
		LinkedList list = new LinkedList(); 
		Iterator iter; 
		Integer val; 
		int i; 
		int sizeA = 50; 
		
		for (i = 0; i < sizeA; ++i) {
			list.pushFront(new Integer(i));
		}
		
		if (list.size() != sizeA) {
			return false; 
		}
		
		i = 0; 
		iter = list.begin();
		
		while (iter.hasNext()){
			val = (Integer)iter.next(); 
			if (val.intValue() != sizeA - i - 1){	
				return false; 
			}
			
			++i; 
		}
		
		return true; 
	}
	
	static boolean testFindInList()
	{
		int sizeA = 50; 
		LinkedList list = new LinkedList(); 
		Integer existingVal = new Integer(5);
		Integer nonExistingVal = new Integer(55);
		
		for (int i = 0; i < sizeA; ++i) {
			list.pushFront(new Integer(i));
		}
		
		if (existingVal.equals((Integer)list.find(existingVal).next()) && 
										null == list.find(nonExistingVal)) {
			return true; 
		}
		
		return false; 
	}
}

