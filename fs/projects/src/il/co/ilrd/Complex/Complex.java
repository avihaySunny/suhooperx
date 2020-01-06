package il.co.ilrd.Complex;
import java.lang.Math;
import java.util.Objects;
import java.util.regex.*;

public class Complex implements Comparable<Complex>{
	private double real; 
	private double im; 
	
	private static final String patternString = "^(\\s+)?([+-])?(\\s+)?\\d+(\\.\\d+)?(\\s+)?[+-](\\s+)?\\d+(\\.\\d+)?(\\s+)?[i](\\s+)?$";
	private static final String oneCoeffPattern = "([+-]?)\\d+i?";
	private static final Pattern patternWhole = Pattern.compile(patternString);
	private static final Pattern patternOne = Pattern.compile(oneCoeffPattern);
	
	public Complex(double real, double im) {
		this.real = real; 
		this.im = im; 
	}
	
	public double getReal() {
		return real; 
	}
	
	public double getIm() {
		return im; 
	}
	
	public void setValue(double real, double im) {
		this.real = real; 
		this.im = im;
	}
	
	public void setReal(double real) {
		this.real = real;
	}
	
	public void setIm(double im) { 
		this.im = im;
	}
	
	//calculates norm of z - |z|   
	public double norm()
	{
		return Math.sqrt(Math.pow(real, 2) + Math.pow(im, 2));
	}
	
	public double phase() {
		return Math.atan2(im, real);
	}
	
	public Complex conjugate() {
        return new Complex(real, -im);
    }

	public Complex add(Complex z) {
		return new Complex(real + z.real, im + z.im);
	}
	
	public Complex	 sub(Complex z) {
		return new Complex(real - z.real, im - z.im);
	}
	// multiply's z1 * z2 
	public Complex mul(Complex z)
	{	
		return new Complex(real * z.real - im * z.im, real * z.im + im * z.real);
	}
	//---------------------------------------------------------------
	/* receives String represention of complex number in format of :   
	 * "a +- bi", "+-bi +-a" , "a +-bi". a or b can be zeros. 
	 * if format is not found invalid an exception will be sent to usr 
	 */
    public static Complex stringToComplex (String strToComplex) throws Exception {
		if(!isValidExpression(strToComplex)) 
			throw new Exception("Invalid Expression");
	
		
    	String[] tokens = strToComplex.split(" "); 
  
    	return new Complex(getRealFromToken(tokens), getImFromToken(tokens));
    }
    //------------------------------------------------------------------------
    private static boolean isValidExpression(String expression) {
    	
        Matcher matcherWhole = patternWhole.matcher(expression);
        Matcher matcherOne = patternOne.matcher(expression);
      
        return matcherWhole.matches() || matcherOne.matches(); 
    	
    }	
    //------------------------------------------------------------------------
    private static double getImFromToken(String[] tokens) {
    	boolean isNeg = false; 
    	for (int i = 0; i < tokens.length; ++i) {
    		if (-1 != tokens[i].indexOf("i"))
    		{
    			if (tokens[i].length() == 1)
    				return 1; 
    			if (i != 0) {
    				if (tokens[i - 1].equals("-")) {
    						isNeg = true; 
    				}
    			}
  
    			StringBuffer imaginaryToken = new StringBuffer(tokens[i]);
    			imaginaryToken.deleteCharAt(tokens[i].length() - 1); 
    			
    			if (isNeg) {
    				return -Double.parseDouble(new String(imaginaryToken));
    			}
    			
    			return Double.parseDouble(new String(imaginaryToken));		
    		}
    	}
    	
    	return 0; 
    }
    //------------------------------------------------------------------------
    private static double getRealFromToken(String[] tokens) {
    	boolean isNeg = false; 
    	for (int i = 0; i < tokens.length; ++i) {
    		if (-1 == tokens[i].indexOf("i")){
    			if (tokens[i].length() == 1){
    				char c = tokens[i].charAt(0); 
    				if (c == '+' || c == '-')
    					continue; 
    			}
    			if (i != 0) {
    				if (tokens[i - 1].equals("-")) {
    						isNeg = true; 
    				}
    			}
    			if (isNeg) {
    				return -Double.parseDouble(tokens[i]);
    			}
    			
    			return Double.parseDouble(tokens[i]);
    		}
    	} 
    	
    	return 0; 
    }
    //------------------------------------------------------------------
    @Override
    public int compareTo(Complex otherComplex){
    	double myNorm = this.norm(); 
    	double otherNorm = otherComplex.norm(); 
    	
    	if (myNorm > otherNorm)	return 1; 
    		
    	else if (otherNorm > myNorm) return -1;
    
		return 0;
    		
    }
    //------------------------------------------------------------------
    @Override
    public boolean equals(Object toCompare){
    	if(toCompare == null)
    		return false; 
    	if (getClass() != toCompare.getClass())
    		return false;
    	
    	Complex exp = (Complex)toCompare; 
    	return real == exp.real && im == exp.im; 
    } 
    //------------------------------------------------------------------
    @Override
    public int hashCode(){
    	return Objects.hash(real, im);
    } 
    //------------------------------------------------------------------
    @Override
    public String toString(){
    	if (real == 0) 
    		return im + "i";
        if (im == 0) 
        	return real + "";
        if (im <  0) 
        	return real + " - " + (-im) + "i";
        
        return real + " + " + im + "i";
    }
	//--------------------------------------------------------------------------
    public boolean isImaginary() {
    	return real == 0 && im != 0; 
    }
    //------------------------------------------------------------------------
    public boolean isReal() {
    	return real != 0 && im == 0; 
    }
}
	