import java.io.BufferedReader;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.fasterxml.jackson.databind.ObjectMapper;

/**
 * Servlet implementation class Companies
 */
@WebServlet("/CR")
public class Companies extends HttpServlet {
	private String url = "jdbc:mysql://127.0.0.1:3306/";
	private String tableName = "CompanyDetails"; 
	private String dbName = "IOTData"; 
	private CRUDSQL sqlHandler; 
	private static ObjectMapper mapper = new ObjectMapper(); 
	private static final long serialVersionUID = 1L;
	private HttpURLConnection conn; 
	private String forwardingURL; 
       
    /**
     * @throws Exception 
     * @throws MalformedURLException 
     * @see HttpServlet#HttpServlet()
     */
    public Companies() throws MalformedURLException, Exception {
        super();
       sqlHandler = new CRUDSQL(url, "root", "password", dbName, tableName);
       conn = setUpConnection(new URL(forwardingURL)); 
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// Set response content type
	      response.setContentType("text/html");

	      // Actual logic goes here.
	      PrintWriter out = response.getWriter();
	      out.println("<h1>" + " new Comapny Registration is here" + "</h1>");
		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try {
			CompanyDetails company = new CompanyDetails(request);
			company.insertToDB(sqlHandler);
			forwardRequest(forwardingURL, company);
			response.setContentType("text/html");
			PrintWriter out = response.getWriter();
	    	out.println("<h1>" +"<p> Company has been entered to db</p> </h1>");  	
		
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}
	
	private String getBody(HttpServletRequest req) {
		
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
	
	@SuppressWarnings("unchecked")
	private static Map<String, String> getMap(String body) throws Exception{
		
		Map<String, String> map = new HashMap<>(); 
		map = mapper.readValue(body, Map.class);
		
		return map; 
	}
	
	private void forwardRequest(String forwardingURL, CompanyDetails company) {
		try {
			String json = mapper.writeValueAsString(company);
			sendPost(json, conn.getOutputStream());
		
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}
	
	private static void sendPost(String body, OutputStream stream) throws IOException {
		OutputStreamWriter writer = new OutputStreamWriter(stream); 
		writer.write(body);
		writer.flush();
		writer.close();
	}
	
	private static HttpURLConnection setUpConnection(URL url) throws Exception {
		HttpURLConnection conn;
		conn = (HttpURLConnection) url.openConnection(); 
		conn.setRequestMethod("POST");
		conn.setDoOutput(true);
		
		return conn; 
	}
	
	private class CompanyDetails {
		@SuppressWarnings("unused")
		private String type = "/CR"; 
		private String name; 
		private String email; 
		private String phone; 
		
		public CompanyDetails(HttpServletRequest request) throws Exception {
			Map<String, String> values = getMap(getBody(request)); 
			this.name = values.get("companyName"); 
			this.email = values.get("email"); 
			this.phone = values.get("phone"); 
		}
		
		public void insertToDB(CRUDSQL sqlHandler) {
			String query = "INSERT INTO " + tableName + " (name, email, phone)" +  " VALUES('" + name + "','"+email+"','" + phone +"')" ;
			sqlHandler.create(query); 
		}
	}
	
}


