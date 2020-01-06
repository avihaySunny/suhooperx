import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class Person implements Serializable{

	private static final long serialVersionUID = 1L;
	private String name; 
	private int age; 
	private transient int height;
	
	public Person(String name, int age, int height) {
		this.name = name; 
		this.age = age; 
		this.height = height; 
	}
	
	public Person(int age, int height) throws IOException{
		name = userInputName(); 
		this.age = age; 
		this.height = height; 
	}
	
	private String userInputName() throws IOException {
			return  new BufferedReader(new InputStreamReader(System.in)).readLine();  	 
	}
	
	public void writeToFile() throws IOException  {
		boolean exists = new File("persons.txt").exists();
		FileOutputStream fout = new FileOutputStream("persons.txt", exists); 
		ObjectOutputStream objSt = exists ? 
	            new ObjectOutputStream(fout) {
	                protected void writeStreamHeader() throws IOException {
	                    reset();
	                }
	            } : new ObjectOutputStream(fout);        
	            
		objSt.writeObject(this);
		objSt.flush();
		fout.close();
		objSt.close();
	}
	
	public Person readFromFile() throws IOException, ClassNotFoundException{
		FileInputStream fin = new FileInputStream("persons.txt"); 
		ObjectInputStream objSt = new ObjectInputStream(fin); 
		
		Person p = (Person)objSt.readObject(); 
		objSt.close(); 
		
		return p; 
	}
	
	public void printPerson() {
		System.out.println("Name : " + name);
		System.out.println("age : " + age);
		System.out.println("height : " + height);
	}
	
	
	public static void main(String[] args) throws IOException, ClassNotFoundException{
		Person a = new Person(20, 100); 
		a.printPerson();
		a.writeToFile(); 
		Person b = a.readFromFile(); 
		b.printPerson();
		
	}
}
