

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;


public class CRUDSQL implements CRUD<String, String>{
	protected Connection conn;
	private String dbName; 
	private String tableName; 
	private String url; 
	private String password; 
	private String username; 
	
	
	public CRUDSQL (String url, String user, String password, String dbName, String tableName) throws SQLException {	
		this.dbName = dbName;
		this.tableName = tableName; 
		this.url = url; 
		this.password = password; 
		this.username = user; 
		
		connect(); 
	}
	
	private void connect() throws SQLException {
		if (conn  == null || conn.isClosed()) {
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
            
            } catch (ClassNotFoundException e) {
                throw new SQLException(e);
            }
         
            conn = DriverManager.getConnection(url + dbName, username, password);
		}
	}
	
	public void close() throws SQLException {
		conn.close();
	}
	
	/*
	 * adds new entry 
	 */
	
	@Override
	public String create(String query) {
		try {
			Statement st = conn.createStatement();
			st.executeUpdate(query);
			//st.executeQuery(query);
			return null; 
		}catch (Exception e) { 
			return null; 
		}
	}

	/*
	 * reads entry using id 
	 */

	@Override
	public String read(String query) {
		try {
			Statement st = conn.createStatement(); 
			ResultSet data = st.executeQuery(query);
			String message = null; 
			
			while(data.next()) {
				message = data.getString("message"); 
			}
			
			return message; 
			
		}catch (Exception e) {
			e.printStackTrace(); 
			return null; 
		}
		
	}

	@Override
	public void update(String key, String query) {
		try {
			PreparedStatement st = conn.prepareStatement(query); 
			st.executeUpdate();
		}catch (Exception e) {
			// TODO: handle exception
		}
	}

	@Override
	public void delete(String key) {
		try {
			String query = "DELETE FROM " + tableName + " WHERE ID = ? "; 
			PreparedStatement st = conn.prepareStatement(query); 
			st.execute(); 
			
		}catch (Exception e) {
			// TODO: handle exception
		}	
	}
}
