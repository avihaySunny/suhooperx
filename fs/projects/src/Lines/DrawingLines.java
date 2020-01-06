package Lines;

import java.awt.Frame;
import java.awt.Graphics;

public class DrawingLines extends Frame
{
  public DrawingLines()
  {          // the following 3 lines creates an empty frame
    setSize(300, 350);
    setVisible(true);
    
  }
  public void paint(Graphics g)
  {
	Boundary b1 = new Boundary(150, 180, 150,110); 
	Boundary b2 = new Boundary(130, 170, 150, 110);
	Ray r1 = new Ray(115, 25, 25); 
	//g.drawLine(b1.a.x, b1.a.y,b1.b.x, b1.b.y);
	System.out.println(r1.p1.x + r1.p1.y + r1.p2.x + r1.p2.y);
   // g.drawLine(r1.p1.x,r1.p1.y,r1.p2.x, r1.p2.y);
    //g.drawLine(b2.a.x, b2.a.y,b2.b.x, b2.b.y);
    
  }
  public static void main(String args[])
  {
    new DrawingLines();
  }
}