

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.fasterxml.jackson.core.JsonFactory;
import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.core.JsonToken;

/**
 * Servlet implementation class LoginHandler
 */
@WebServlet("/LoginHandler")
public class LoginHandler extends HttpServlet {
	private String url = "jdbc:mysql://127.0.0.1:3306/";
	private String tableName = "Companies"; 
	private String dbName = "IOTData"; 
	private CRUDSQL sqlHandler;  
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public LoginHandler() throws SQLException {
        super();
        sqlHandler = new CRUDSQL(url, "root", "password", dbName, tableName); 
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		 response.setContentType("text/html");
	      PrintWriter out = response.getWriter();
	      out.println("<h1>" + " this is login" + "</h1>");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		retrieveDataFromRequest(request);
		
	}
	
	private String retrievePasswordQuery(HttpServletRequest req, String companyName) {
		String query = "SELECT password from " + tableName + " where NAME = '" + companyName + "'; " ;
	}
	

	/*
	 * appends user body request from parsing 
	 */
	private String getStringFromRequest(HttpServletRequest req) {
		
		StringBuffer js = new StringBuffer();
		String line; 
		try {
			BufferedReader reader = req.getReader(); 
			while ((line = reader.readLine()) != null) {
				js.append(line); 
			}	
		} catch (Exception e) {
			// TODO: handle exception
		}
		return js.toString().replaceAll("\\s+", ""); 
	}
	
	/*
	 * parses user request and get details 
	 */
	@SuppressWarnings("static-access")
	private void retrieveDataFromRequest(HttpServletRequest req) {
		String companyName ; 
		String password; 
		try {
				
				String json  = getStringFromRequest(req); 
				JsonFactory factory = new JsonFactory(); 
				JsonParser parser = factory.createParser(json); 
				
				while(!parser.isClosed()){
					 JsonToken jsToken = parser.nextToken(); 
					 
					 if (jsToken.FIELD_NAME.equals(jsToken)) {
						 String fieldName = parser.getCurrentName();
						 if (fieldName.contentEquals("USERNAME")){
							 jsToken = parser.nextToken();  
							 companyName = parser.getValueAsString(); 
						 }
						 
						 if (fieldName.contentEquals("PASSWORD")) {
							 jsToken = parser.nextToken();
							 password = parser.getValueAsString(); 
						 }
					 }
				}	

			}catch (Exception e) {
				e.printStackTrace();
			}
	}
}
