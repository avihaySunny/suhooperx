package resources;

import java.awt.Image;

import javax.swing.ImageIcon;

public class GameComponent {
	private String url; 
	private Image img; 
	private int width; 
	private int height; 
	
	public GameComponent(String url) {
		this.url = url; 
		initBackground(); 
		
	}
	
	private void initBackground() {
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
