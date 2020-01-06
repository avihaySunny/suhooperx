package fs;

public class Rectangle extends Shape {

	double width; 
	private double height; 
	
	public Rectangle() {
		//default rectangle is a 1x1 rectangle
		this.width = 1; 
		this.height= 1; 
	}
	
	public Rectangle(double height, double width) {
		this.width = height;  
		this.height= width; 
	}
	
	public Rectangle(double height, double width, String color, boolean is_filled) {
		super(color, is_filled);  
		this.width = height;  
		this.height= width; 
	}
	
	public void setHeight(double height) {
	
		this.height = height; 
	}
	
	public void setWidth(double width) {
	
		this.width = width;
	}
	
	public double getHeight() {
	
		return this.height;
	}
	
	public double getWidth() {
		
		return this.width;
	}
	
	public double getArea()
	{
		return this.height * this.width; 
	}
	
	public double getPerimeter()
	{
		return 2 * this.height + 2* this.width; 
	}

	@Override
	public String toString()
	{
		return "A rectangle with width : " + this.width + " and length : " + this.height;
	}
}

