package il.co.ilrd.SingletonWS;

public class DoubleCheckLock 
{
	 private static DoubleCheckLock instance;  
	 
	 public static DoubleCheckLock getInstance()
	 {	 
		 if (instance == null){	
			 synchronized (DoubleCheckLock.class){
				 if (instance == null) {
					 instance = new DoubleCheckLock(); 
				 } 
			 }
	 }
		 
		 return instance; 
	 }
}
