import java.awt.event.KeyEvent;
/*
 * Written by Avihay Asraf, Nov 19 
 * this class implements boat component, the only 
 * game object the user can interact with  
 */

public class Boat extends Sprite{
	public Boat(String url) { 
		super(url, BOAT_START_X, BOAT_START_Y, 0);
	}
	
	/*
	 * handler for keyPress event for boat movement 
	 */
	public void whenKeyPress(KeyEvent keyPress) {
		switch (keyPress.getKeyCode()){
			case  KeyEvent.VK_LEFT : 
				setSpeed(-BOAT_SPEED); 
				break; 
			case  KeyEvent.VK_RIGHT : 
				setSpeed(BOAT_SPEED);
				break; 
		}
	}
	
	public void whenKeyRelease(KeyEvent keyPress) {
		switch (keyPress.getKeyCode()){
		case  KeyEvent.VK_LEFT : 
			setSpeed(0); 
			break; 
		case  KeyEvent.VK_RIGHT : 
			setSpeed(0); 
			break; 
		}
	}

}
