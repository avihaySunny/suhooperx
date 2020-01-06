
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import resources.GameComponent;

public class Boat extends GameComponent{
	private int xSpeed;
	private int xPosition = 640; 
	private int yPosition = 500; 
	
	public Boat(String url) { 
		super(url);
	}
	
	public void move() {
		xPosition += xSpeed; 
		if (xPosition < -getWidth()) {
			xPosition = Config.BORDER_LENTGH; 
		}
		
		else if (xPosition > Config.BORDER_LENTGH ) {
			xPosition = -getWidth(); 
		}
	}
	
	public int getXPos() {
		return xPosition; 
	}
	
	public int getYPos() {
		return yPosition; 
	}
	
	public void whenKeyPress(KeyEvent keyPress) {
		switch (keyPress.getKeyCode()){
			case  KeyEvent.VK_LEFT : 
				xSpeed = -3; 
				break; 
			case  KeyEvent.VK_RIGHT : 
				xSpeed = 3;
				break; 
		}
	}
	
	public void whenKeyRelease(KeyEvent keyPress) {
		switch (keyPress.getKeyCode()){
		case  KeyEvent.VK_LEFT : 
			xSpeed = 0; 
			break; 
		case  KeyEvent.VK_RIGHT : 
			xSpeed = 0;
			break; 
		}
	}
	
	public Rectangle getBorders() {
		return new Rectangle(xPosition, yPosition, getWidth(), getHeight()); 
	}
}
