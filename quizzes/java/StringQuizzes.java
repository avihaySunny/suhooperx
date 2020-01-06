import java.lang.*;
public class StringQuizzes {
	public static void main(String[] args) {
		
		System.out.println(isPalindrom("122221"));
		System.out.println(isPalindrom("1226221"));
		System.out.println(isPalindrom("1325221"));
		printBackwards("hello");
		permuations("avihay");
	}
	
	private static boolean isPalindrom(String str) {
		int len = str.length() - 1;
		int i = 0; 
		 
		while ((str.charAt(i) == str.charAt(len - i)) && (i <= len/2)){
			++i;
		}
		
		return (i == (len / 2)) || (i == 1 + (len/2)); 
	}
	
	private static void printBackwards(String str) {
		for (int i = str.length() - 1; i >= 0; --i) {
			System.out.print(str.charAt(i));
		}
		System.out.println("");
	}
	
	private static void permuations(String str) {
		permuationsRec(0, new StringBuilder(str));
	}
	
	private static void permuationsRec(int indx, StringBuilder str) {
		if (indx == str.length()) {
			System.out.println(str);
			return; 
		}
			for (int i = indx; i < str.length(); ++i) {
			permuationsRec(i + 1, swapChar(i, indx, str));
		}
	}
	
	private static StringBuilder swapChar(int i, int j, StringBuilder str) {
		StringBuilder swappedStr = new StringBuilder(str);
		char tmp = str.charAt(i); 
		swappedStr.setCharAt(i, str.charAt(j));
		swappedStr.setCharAt(j, tmp);
		
		return swappedStr;
	}
}
