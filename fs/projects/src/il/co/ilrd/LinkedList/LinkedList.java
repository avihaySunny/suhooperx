package il.co.ilrd.LinkedList;

public class LinkedList{
	private Node head; 
	private int size;
	
	public LinkedList() {}; 
	
	public LinkedList(Object data)
	{
		head = new Node(data, null);  
		size = 0; 
	}
	
	public void pushFront(Object data)
	{ 
		Node newNode = new Node(data, head); 
		head = newNode;
		++size; 
	}
	
	/* 
    * returns current head's objects
	* not valid on empty list.
	*/ 
	public Object popFront(){
		Object data = head.data;
		head = head.nextNode; 
		--size; 
		
		return data; 
	}
	/*
	 * returns size of list
	 */
	public int size(){
		return size; 
	}
	
	public boolean isEmpty(){
		return head == null; 
	}
	
	public Iterator find(Object data){
		Node runner = head;  
		if (data == null){
			return null; 
		}
		while(runner != null && false == runner.data.equals(data)){
			runner = runner.nextNode; 
		}
		
		if (null == runner){
			return null;
		}
			 
		return new LinkedListIterator(runner);
	}
	
	/*
	 * returns lists head if exists 
	 */
	public Iterator begin()
	{
		return new LinkedListIterator(head); 
	}
	
	private class Node{
		private Object data;
		private Node nextNode; 
		
		private Node(Object data, Node nextNode)
		{
			this.data = data; 
			this.nextNode = nextNode; 
		}
}
	
	private class LinkedListIterator implements Iterator{
		private Node currentNode;
		
		private LinkedListIterator(Node node)
		{
			currentNode = node; 
		}
		@Override 
		public boolean hasNext()
		{
			return currentNode != null; 
		}
		@Override
		public Object next() {
			Object data = currentNode.data; 
			currentNode = currentNode.nextNode; 
			
			return data; 
		}
	}
}

