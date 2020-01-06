import java.awt.Rectangle;

/*
 * Written by Avihay Asraf, Nov 19 
 * this class implements a moving image 
 * for the plane and is the base for 
 * parachuter and boat classes   
 */

public abstract class Sprite extends GameStaticComponent implements Config{
	private int axisSpeed; 
	private int xPosition;
	private int yPosition; 
	
	public Sprite(String url, int x, int y, int speed) {
		super(url); 
		axisSpeed = speed; 
		xPosition = x; 
		yPosition = y; 
	}
	
	public void move() {
		xPosition += axisSpeed;  
			//looping around the window borders 
		if (xPosition < -getWidth()) {
			xPosition = X_BORDER_LIMIT; 
		}
		else if (xPosition > X_BORDER_LIMIT ) {
			xPosition = -getWidth(); 
		}
	}
	
	public int getXPos() {
		return xPosition; 
	}
	
	public int getYPos() {
		return yPosition; 
	}
	
	public void setXpos(int x) {
		xPosition = x; 
	}
	public void setYpos(int y) {
		yPosition = y; 
	}
	
	public Rectangle getBorders() {
		return new Rectangle(xPosition, yPosition, getWidth(), getHeight()); 
	}
	
	public void setSpeed(int speed) {
		axisSpeed = speed;
	}
	
	public int getSpeed() {
		return axisSpeed; 
	}
}
