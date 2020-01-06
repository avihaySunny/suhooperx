import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;

public class URLReader {
	public static void main(String[] args){
		try {
			URL oracle = new URL("http://www.google.com/");
			FileWriter page = new FileWriter("/home/student/Desktop/web.html");
			
			InputStream is = oracle.openConnection().getInputStream();
			BufferedReader reader = new BufferedReader( new InputStreamReader( is )  );
	        
	        String inputLine;
	        while ((inputLine = reader.readLine()) != null)
	        	page.write(inputLine);
	            System.out.println(inputLine);
	        reader.close();
	        page.close();
		}catch(Exception e ) {System.out.println(e.getMessage());
		
		}
	}
}
