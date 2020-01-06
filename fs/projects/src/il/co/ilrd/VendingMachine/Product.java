package il.co.ilrd.VendingMachine;

public class Product {
	private double price; 
	private String productName;
	
	public Product(float price, String productName) {
		this.price = price;
		this.productName = productName;
	}
	
	public double getPrice() {
		return price;
	}
	public void setPrice(float price) {
		this.price = price;
	}
	public String getProductName() {
		return productName;
	}

	
}
