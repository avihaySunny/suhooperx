package il.co.ilrd.SQL;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import il.co.ilrd.CRUD.crud;

public class CRUDSQL implements crud<String, Integer>{
	private Connection conn;
	private String dbName; 
	private String tableName; 
	
	static {
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public CRUDSQL(String url, String user, String password, String dbName, String tableName) throws ClassNotFoundException {
		try{	
			this.dbName = dbName;
			this.tableName = tableName; 
			conn = DriverManager.getConnection(url + this.dbName,user,password); 
				
		}catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void close() throws SQLException {
		conn.close();
	}
	
	/*
	 * adds new entry 
	 */
	
	@Override
	public Integer create(String item) {
		try {
			Statement st = conn.createStatement();
			item = item.replaceAll("'", "");
			String query = "INSERT INTO " + tableName + " (message)" +  " VALUES('" + item + "');" ;  
			System.out.println(query);
			
			return st.executeUpdate(query); 
		
		}catch (Exception e) { return null; }	 
	}

	/*
	 * reads entry using id 
	 */

	@Override
	public String read(Integer key) {
		try {
			Statement st = conn.createStatement(); 
			ResultSet data = st.executeQuery("SELECT message FROM " + tableName + " WHERE id =" + key + " ;");
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
	public void update(Integer key, String message) {
		try {
			String query = "UPDATE " + tableName + " SET message = ? WHERE id = ?"; 
			//System.out.println(query);
			PreparedStatement st = conn.prepareStatement(query); 
			st.setString(1, message);
			st.setInt(2, key);
			st.executeUpdate();
		}catch (Exception e) {
			// TODO: handle exception
		}
	}

	@Override
	public void delete(Integer key) {
		try {
			String query = "DELETE FROM " + tableName + " WHERE ID = ? "; 
			PreparedStatement st = conn.prepareStatement(query); 
			st.setInt(1, key);
			st.execute(); 
			
		}catch (Exception e) {
			// TODO: handle exception
		}	
	}
}
