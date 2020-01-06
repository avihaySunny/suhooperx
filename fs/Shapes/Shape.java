package fs;

public abstract class Shape {
	
	private String color; 
	private boolean filled; 
	
	abstract String getColor();
	
	abstract boolean getFilled();
	
	abstract void setFilled(boolean filled);
	
	abstract String toString();

}




