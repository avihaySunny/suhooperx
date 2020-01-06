package il.co.ilrd.CRUD;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CRUDFile implements crud<String, String>{
	File file; 
	BufferedWriter writer; 
	
	public CRUDFile(String pathname) throws IOException {
		file = new File(pathname);
		writer = new BufferedWriter(new FileWriter(file, true));
	}
	
	@Override
	public void close() throws Exception {
		writer.close();	
	}

	@Override
	public String create(String item) {
		try {
			
			writer.write(item + "\n");
			writer.flush();
			 
			return null; 
		} catch (IOException e) {return null; } 
	}

	@Override
	public String read(String key) {

		return null;
	}

	@Override
	public void update(String key, String item) {}

	@Override
	public void delete(String key) {
		
	}

}
