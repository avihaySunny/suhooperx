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
 * Servlet implementation class Products
 */
@WebServlet("/Products")
public class Products extends HttpServlet {
	private String url = "jdbc:mysql://127.0.0.1:3306/";
	private String tableName = "Products"; 
	private String dbName = "IOTData"; 
	private CRUDSQL sqlHandler;  
	private static final long serialVersionUID = 1L;
	private String productName; 
	private String productCompany; 
	private String forwardingURL; 
    private static ObjectMapper mapper = new ObjectMapper(); 
    private HttpURLConnection conn; 
    /**
     * @throws Exception 
     * @throws MalformedURLException 
     * @see HttpServlet#HttpServlet()
     */
    public Products() throws MalformedURLException, Exception {
        super();
        sqlHandler = new CRUDSQL(url, "root", "password", dbName, tableName); 
        conn = setUpConnection(new URL(forwardingURL)); 
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		  response.setContentType("text/html");
	      PrintWriter out = response.getWriter();
	      out.println("<h1>" + " new Product Registration is here" + "</h1>");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try {
			ProductDetails current =  new ProductDetails(request);
			current.insertToDB(sqlHandler);
			forwardRequest(forwardingURL, current); 
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		};
		
		  PrintWriter out = response.getWriter();
	      out.println("<h1>" + " new Product Registration is" +productCompany + ":" + productName + " </h1>");
	}
	
	private static HttpURLConnection setUpConnection(URL url) throws Exception {
		HttpURLConnection conn;
		conn = (HttpURLConnection) url.openConnection(); 
		conn.setRequestMethod("POST");
		conn.setDoOutput(true);
		
		return conn; 
	}
	
	private static void sendPost(String body, OutputStream stream) throws IOException {
		OutputStreamWriter writer = new OutputStreamWriter(stream); 
		writer.write(body);
		writer.flush();
		writer.close();
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
		System.out.println(js);
		return js.toString().replaceAll("\\s+", ""); 
	}
	
	@SuppressWarnings("unchecked")
	private static Map<String, String> getMap(String body) throws Exception{
		 
		Map<String, String> map = new HashMap<>(); 
		map = mapper.readValue(body, Map.class);
		
		return map; 
	}
	
	private void forwardRequest(String forwardingURL, ProductDetails product) {
		try {
			String json = mapper.writeValueAsString(product);
			sendPost(json, conn.getOutputStream());
		
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}

	private class ProductDetails {
		private String cmpname; 
		private String name; 
		private String model; 
		@SuppressWarnings("unused")
		private String type = "/PR";
		
		public ProductDetails(HttpServletRequest request) throws Exception {
			Map<String, String> values = getMap(getBody(request)); 
			this.cmpname = values.get("companyName"); 
			this.name = values.get("productName"); 
			this.model = values.get("model"); 
		}
		
		public void insertToDB(CRUDSQL sqlHandler) {
			String query = "INSERT INTO " + tableName + " (NAME, ProducerName, MODEL)" +  " VALUES('" + cmpname + "','"+name+"','" + model +"');" ;
			System.out.println(query);
			sqlHandler.create(query); 
		}
		
	}
	

	
}
