/*
	 * Written by Avihay Asraf, Nov 19 
	 * this class implements the 
	 * parachuter object which randomly falls 
	 * from the sky   
	 */

public class Parachuter extends Sprite{
	private boolean currentlyFalling; 
	
	public Parachuter(String url) {
		super(url, PARACHUTER_START_X, PARACHUTER_START_Y, PARACHUTE_DROP_SPEED); 
	}
	
	// only game object that moves on the y direction 
	@Override
	public void move() {
		setYpos(getYPos() + getSpeed());
	}

	public void setX(int x) {
		setXpos(x); 
	}
	
	public boolean getFalling() {
		return currentlyFalling; 
	}
	
	public void setFalling(boolean val) {
		currentlyFalling = val; 
	}
	
	public void resetYPos() {
		setYpos(PLANE_Y_POS);  
	}
}

