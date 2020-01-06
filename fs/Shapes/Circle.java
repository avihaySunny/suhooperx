package fs;
import java.awt.Frame;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;
import java.lang.Math;

import javax.swing.JFrame;

import com.sun.prism.Graphics;

interface ShapeActions{
	public void drawShape(Graphics g); 
}


public class Circle extends Shape{
	private double radius; 
	  
	public Circle() {
		this.radius = 1; 
	}
	
	public Circle(double radius) {
		this.radius = radius; 
	}
	
	public Circle(double radius, String color, boolean is_filled) {
		super(color, is_filled); 
		this.radius = radius; 
	}
	
	public double getArea() {
		
		return Math.pow(this.radius, 2) * Math.PI;
	}
	
	public double getPrimeter() {
		
		return  this.calcPerim(Math.PI, this.radius);
	}
	
	private double calcPerim(double pi, double radius){
		return 2 * pi * radius;
	}
}

