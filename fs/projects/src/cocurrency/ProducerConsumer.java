package cocurrency;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class ProducerConsumer {
	public static void main(String[] args) throws InterruptedException{
		ProductQ q = new ProductQ(); 
		Consumer consumer = new Consumer(q); 
		Producer producer = new Producer(q); 
		Consumer consumer2 = new Consumer(q); 
		
		consumer.join();
		consumer2.join();
		producer.join();
	}
	
	
}
class Producer extends Thread {
	ProductQ q; 
	
	public Producer(ProductQ q) {
		this.q = q; 
		this.setName("Producer");	
		this.start();
	}
	
	@Override
	public void run() {
		AtomicInteger i = new AtomicInteger(0); 
		
		while(true) {
				i.getAndIncrement(); 
				try {
					q.putProductIntoQ(i);
					if(i.intValue() > 100) {i.set(0);}
				} catch (InterruptedException e) {
					e.printStackTrace();
					
				}
		}
	}
}

class Consumer extends Thread{
	ProductQ q; 
	
	public Consumer(ProductQ q) {
		this.q = q; 
		this.setName("Consumer");
		this.start();

	}
	
	@Override
	public void run() {
		while(true) {
			try {
				q.getProductFromQ();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

}	
class ProductQ { 
	Semaphore semProd = new Semaphore(1);
	Semaphore semCon = new Semaphore(0);
	AtomicInteger productId; 
	public ProductQ() {}
	public void putProductIntoQ(AtomicInteger productId) throws InterruptedException{
		semProd.acquire();
		this.productId = productId; 
		System.out.println(Thread.currentThread().getName()+" Putting(In Q) Product ID:"+productId);
		
		semCon.release();
	}
	
	public void getProductFromQ() throws InterruptedException {
		semCon.acquire(); 
		System.out.println(Thread.currentThread().getName()+" Getting(In Q) Product ID:"+productId);
		semProd.release();
	}
	
}
