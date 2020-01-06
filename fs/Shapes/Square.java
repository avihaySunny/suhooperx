package fs;

public class Square extends Rectangle {
	private double side; 
	
	public Square(){
		this.side = 1; 
	}
	
	public Square(double side){
		this.side = side; 
	}
	
	public Square(double side, String color, boolean is_filled){
		super(side, side, color, is_filled);
		this.side = side; 
	}
	
	public void setSide(double side) {
		this.side = side; 
	}
	
	public double getSide(double side) {
		return this.side; 
	}
	

}
