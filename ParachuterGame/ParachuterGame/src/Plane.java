import resources.GameComponent;

public class Plane extends GameComponent{
	private final int dx = -3; 
	private int xPosition = Config.BORDER_LENTGH ; 
	private int yPosition = Config.PLANE_Y_POS; 
	
	public Plane(String url) {
		super(url);
	}

	public void move() {
		xPosition += dx; 
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
}
