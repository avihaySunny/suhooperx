package il.co.ilrd.FileTree;

public class TreeFileTest {
	
	public static void main(String[] args) {
		String def_path = new String ("/home/student/");  
		Tree mytree = null; 
		
		if (args[0] != null) 
			def_path = args[0];
		
		try {
			mytree = new Tree(def_path);
			mytree.print();

		}catch (Exception e) {
			System.out.println(e.getMessage());
		}

			
	}
}

