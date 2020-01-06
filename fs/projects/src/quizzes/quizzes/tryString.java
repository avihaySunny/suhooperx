package quizzes;

import java.util.Arrays;
import java.util.stream.Stream;

public class tryString {

	public static void main(String[] args) {
		Runnable r = new Runnable() {
			@Override
			public void run() {
				int x = 0; 
				while (x < 100000) {
					System.out.println("X");
					++x;
					try{
						wait(1000L);
					}catch (Exception e) {
						System.out.println("Caught 1");
					}
				}
			}
		};
		
		Thread t1 = new Thread(r); 
		try {

			t1.start();
			t1.interrupt();
			
		} catch (Exception e) {}
		
	}
	
	
	public static int strstr(String s1, String s2) {
		int j = 0 , i = 0, prevIndx; 
		for (i = 0; i < s1.length(); ++i) {
			prevIndx = i; 
			while (s1.charAt(i) == s2.charAt(j)) {
				++i; 
				++j; 
				
				if (j == s2.length()) {
					return i - j; 
				}
			}
			j = 0; 
			i = prevIndx; 
		}
		
		return -1;
	}
	
public static int[] allRowSum(int [][] matrix) {
		int[] sumArr = new int[matrix.length]; 
		
		for (int i = 0; i < sumArr.length; ++i) {
			for (int j = 0; j < matrix[0].length; ++j) {
				sumArr[i] += matrix[i][j];
			};
		}		
		return sumArr;
	}



}
