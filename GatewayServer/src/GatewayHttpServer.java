

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.InetSocketAddress;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.function.Consumer;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;

public class GatewayHttpServer {
	private HttpRequests requestsHandlers; 
	private static int nThreads = 3; 
	private static ExecutorService executer = Executors.newFixedThreadPool(nThreads); 
	private static String tomcatURL = "http://127.0.0.1:8081/Servlets"; 
	
	private static void submitTask(String body) {
		
		executer.submit(()-> {
			HttpURLConnection conn;
			/*
			 * 1. get JSON map 
			 * 2. send it to the command factory
			 * 3. get to where to send
			 * 4. post http request  
			 */
			
			try {
				int counts = 0; 
				Map<String ,String> pairs = getJsonPairs(body);
				String type = pairs.get("type"); 
				
				GatewayHttpServer.CommandFactory command  = GatewayHttpServer.CommandFactory.create(type);
				
				URL url = new URL(tomcatURL + command.getPath());
				conn = setUpConnection(url); 
				sendPost(body, conn.getOutputStream());
				while(200 != conn.getResponseCode() && counts < 3) {
					sendPost(body, conn.getOutputStream());
					++counts; 
				}
				
			}catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} 
		}); 
	}
	
	public GatewayHttpServer(int port) throws IOException {
		requestsHandlers = new HttpRequests(port, GatewayHttpServer::submitTask);
		executer = Executors.newFixedThreadPool(nThreads);
	}
	
	public void startServer() {
		requestsHandlers.startHttpServer(); 
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
	@SuppressWarnings("unchecked")
	private static Map<String, String> getJsonPairs(String body) throws Exception{
		ObjectMapper mapper = new ObjectMapper(); 
		Map<String, String> map = new HashMap<>(); 
		map = mapper.readValue(body, Map.class);
		
		return map; 
	}
	
 	private static class HttpRequests {
	  private HttpServer server; 
	  private String requestsPath = "/requests"; 
	  private HttpContext rqContext; 
	  private static Consumer<String> submit; 
  
	  public HttpRequests(int port, Consumer <String> submit) throws IOException {
		server = HttpServer.create(new InetSocketAddress(port), 0); 
		rqContext = server.createContext(requestsPath);
		rqContext.setHandler(HttpRequests::handleRequest);
		HttpRequests.submit = submit; 
		
		
	  }

	  private static void handleRequest(HttpExchange exchange) throws IOException {
		  submit.accept(getBody(exchange.getRequestBody()));
		  System.out.println(getBody(exchange.getRequestBody()));
		  String response = "request server running"; 
	      exchange.sendResponseHeaders(200, response.getBytes().length);
	      OutputStream os = exchange.getResponseBody();
	      os.write(response.getBytes());
	      os.close();
	  }
	  
	  private void startHttpServer() {
		  server.start();
	  }
	  private static String getBody(InputStream stream){
		  BufferedReader buff = new BufferedReader( new InputStreamReader(stream)); 
		  StringBuilder body = new StringBuilder();  
		  String line; 
		  try {
			  while((line = buff.readLine()) != null ){
				  body.append(line); 
			  }
			  
		  }catch (Exception e) {
			
		  }
		  return new String(body); 
	  }
  }
 	
 	public enum CommandFactory {
 		CR{
 			@Override
 			public String getPath() {
 				return new String("/CR"); 
 			}
 		}, 
 		
 		PR {
 			@Override
 			public String getPath() {
 				return new String("/PR"); 
 			}
 		}, 
 		
 		IOT_DATA{
 			@Override
 			public String getPath() {
 				return new String("/IOT_DATA"); 
 			}
 		}; 
 		
 		public static CommandFactory create(String type) { 
 			switch (type) {
 				case "CR" : 
 					return CommandFactory.CR; 
 				case "PR" : 
 					return CommandFactory.PR; 
 				case "IOT_DATA":
 					return CommandFactory.IOT_DATA;  	
 				default : 
 					return null;
 			}
 		}

 		public String getPath() {
 			return new String(""); 
 		}
 		
		public String toString() {
				return new String("Command");  
		}
 	}
}
