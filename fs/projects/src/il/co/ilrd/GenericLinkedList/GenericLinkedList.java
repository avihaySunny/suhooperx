/*
 * Written by Avihay Asraf
 * 27/8/19
 * reviewd by : Gil Kremeer 
 * 
 */

package il.co.ilrd.GenericLinkedList;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericLinkedList <E> implements Iterable <E>{
	E t; 
		
		private Node <E> head; 
		private int size;
		private int stamp; 
	
		public GenericLinkedList() {}
		
		public GenericLinkedList(E data){
			head = new Node<E>(data, null);  
			size = 0; 
		}
		
		public void pushFront(E data){ 
			Node<E> newNode = new Node<E>(data, head); 
			head = newNode;
			++size; 
			++stamp;
		}
		
		public E popFront(){
			E data = head.data;
			head = head.nextNode; 
			--size; 
			++stamp; 
			return data; 
		}
		
		public int size(){
			return size; 
		}
		
		public boolean isEmpty(){
			return head == null; 
		}
		
		public static <E> GenericLinkedList<E> merge(GenericLinkedList<E> listA,GenericLinkedList<E> listB){ 
			GenericLinkedList<E> mergedList = new GenericLinkedList<E>();
			Node<E> runner = listA.head; 
			while (null != runner) {
				mergedList.pushFront(runner.data);
				runner = runner.nextNode; 
			}
			
			runner = listB.head;
			while (null != runner) {
				mergedList.pushFront(runner.data);
				runner = runner.nextNode; 
			}
	  
			return mergedList; 		
		}
	  	
	public Iterator<E> find(E data){
		Node<E> runner = head; 
		for (E curData : this) {
			if (curData.equals(data)){
				return new GenericListIterator(runner);}
			runner = runner.nextNode;
		}
		return null; 
	}
	
	public static <E> GenericLinkedList<E> reverse(GenericLinkedList<E> list) {	   
	   GenericLinkedList<E> reversedList = new GenericLinkedList<E>(); 
	   Node<E> runner = list.head; 
		  
	   while (runner != null) {
		   reversedList.pushFront(runner.data);
		   runner = runner.nextNode; 
	   }
		  
	   return reversedList;   
	}
		
	@Override
	public Iterator<E> iterator() {
		return new GenericListIterator(head);
	}
		
		private static class Node <T>{
			private T data;
			private Node<T> nextNode; 
			
			private Node (T data, Node<T> nextNode){
				this.data = data; 
				this.nextNode = nextNode; 
			}
	}

	private class GenericListIterator implements Iterator<E> {
		private Node<E> currentRef;
		private int iterStamp; 
		
		GenericListIterator(Node <E> node) {
			currentRef = node; 
			iterStamp = stamp; 
		}
		@Override
		public boolean hasNext() {
			return currentRef != null; 
		}

		@Override
		public E next(){
			if(stamp > iterStamp) {
				throw new ConcurrentModificationException();
			}
			
			E data = currentRef.data; 
			currentRef = currentRef.nextNode; 
			return data; 
		}		
	}
}
