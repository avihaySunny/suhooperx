package quizzes;

import java.util.Stack;

public class QueueFromStack {

	private Stack <Object> incoming;
	private Stack <Object> outgoing;
	
	public QueueFromStack() {
		//incoming = new Stack<Object>();
		outgoing = new Stack<Object>();
	}
	
	public static void main(String[] args) {
		QueueFromStack queue = new QueueFromStack();
		
		try {
			for (int i = 0; i < 20; ++i) {
				queue.enqueue(new Integer(i));
			}
			
			for (int i = 0; i < 8; ++i) {
				System.out.println(queue.dequeue());
			}
			
			for (int i = 0; i < 10; ++i) {
				queue.enqueue(new Integer(i));
			}
			
			for (int i = 0; i < 12; ++i) {
				System.out.println(queue.dequeue());
			}
		}catch(RuntimeException e) {
			System.out.println(e.getMessage());
			System.out.println("Oh boy");
		}
		
	}
	
	public void enqueue(Object data) {
		incoming.add(data);
		}
	
	public Object dequeue() {
		if(outgoing.isEmpty()) {
			moveStack(incoming, outgoing);
		}
		return outgoing.pop();
	}
	
	static void moveStack(Stack <Object> sa, Stack <Object> sb) {
		while(!sa.isEmpty()) {
			sb.push(sa.pop());
		}
	}

}
