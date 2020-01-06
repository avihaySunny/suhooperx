
import java.awt.Image;

import javax.swing.ImageIcon;

/*
 * Written by Avihay Asraf, Nov 19 
 * this class implements basic game component - a non moving image 
 */
public class GameStaticComponent {
	private String url; 
	private Image img; 
	private int width; 
	private int height; 
	
	public GameStaticComponent(String url) {
		this.url = url; 
		loadImage();
	}
	
	private void loadImage() {
        ImageIcon ii = new ImageIcon(url);
        img = ii.getImage();
        width = img.getWidth(null); 
        height = img.getHeight(null); 
    }
	 
	public int getWidth() {
		return width; 
	}
	
	public int getHeight() {
		return height; 
	}
	
	public Image getIm() {
		return img; 
	}
}
