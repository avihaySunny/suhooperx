package Lines;

import java.awt.Point;

public class Ray {
 
	int angle; 
	Point p1;
	Point p2; 
	
	public Ray(double angle, int x, int y) {
		p1 = new Point(x, y); 
		p2 = new Point(x + (int)Math.sin(angle), y + (int)Math.cos(angle));  
	}
}
