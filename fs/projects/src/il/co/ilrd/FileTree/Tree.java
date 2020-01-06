package il.co.ilrd.FileTree;

import java.io.File;
import java.util.ArrayList;

public class Tree {
	private TreeComponent root; 
	
	public Tree (String path) {
		root = new DirComposite(path);
	}
	
	public void print() {
		root.print(0);
	}
	
	private abstract class TreeComponent implements Comparable <TreeComponent> {
		String name; 
		void print(int spacing) {} 
		
		@Override
		public int compareTo(TreeComponent object) {
			return this.name.compareTo(object.name);
		}
	}

	private class DirComposite extends TreeComponent {
		 
		private ArrayList<TreeComponent> content_list; 

		DirComposite(String path) throws NullPointerException {
			File fp; 
			File[] files_list;
			fp = new File(path); 
			name = fp.getName();
			files_list = fp.listFiles(); 
			content_list = new ArrayList<TreeComponent>(); 
			
			for (File file : files_list) {
				if (file.isDirectory()) {
					content_list.add(new DirComposite(file.getPath()));
				}
				else {
					content_list.add(new FileLeaf(file.getName()));
				}
			}
	
		content_list.sort(null);	
		}
		
		@Override
		void print(int spaces){
			System.out.println(getSpaces(spaces) + "Folder --" + name);
			for (TreeComponent content : content_list) {
				content.print(spaces + 1);
			}
		}
	}
	
	private class FileLeaf extends TreeComponent implements Comparable <TreeComponent>{
		FileLeaf(String name) {
			this.name = name;
		}
		@Override
		void print(int spaces) {
			System.out.println( getSpaces(spaces) +"File " + name);
		}
	}
	
	private String getSpaces(int numOfSpaces) {
		StringBuffer spaces = new StringBuffer(numOfSpaces);
		for (int i = 0; i < 2 * numOfSpaces; ++i) {
			spaces.append('-'); 
		}
		
		return new String(spaces);
	}
}
