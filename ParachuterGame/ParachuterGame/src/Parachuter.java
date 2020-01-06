
import java.awt.Rectangle;
import resources.GameComponent;

public class Parachuter extends GameComponent{
	private final int dropSpeed = Config.PARACHUTE_DROP_SPEED ; 
	private int yPosition = Config.PARACHUTER_START_Y; 
	private int xPosition = Config.PARACHUTER_START_X;; 
	private boolean currentlyFalling; 
	
	public Parachuter(String url) {
		super(url); 
	}
	
	public void move() {
		yPosition += dropSpeed;
	}
	
	public int getXPos() {
		return xPosition; 
	}
	
	public int getYPos() {
		return yPosition; 
	}

	public void setX(int x) {
		xPosition = x; 
	}
	
	public boolean getFalling() {
		return currentlyFalling; 
	}
	
	public void setFalling(boolean val) {
		currentlyFalling = val; 
	}
	
	public void resetYPos() {
		yPosition = Config.PLANE_Y_POS; 
	}
	
	public Rectangle getBorders() {
		return new Rectangle(xPosition, yPosition, getWidth(), getHeight()); 
	}
}

