package il.co.ilrd.VendingMachine;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Scanner;

public class VMTest {
	private static Scanner scanner;
	
	public static void main(String[] args) {	
	
		LinkedList<Product> productList = initProductList();
		//----------- Display PORT---------------------------
		Display dis = new Display(){
			public void printToDisplay(String toPrint) {
				System.out.println(toPrint);
			}
		}; 
		//--------------------------------------------------
		
		VendingMachine vm = new VendingMachine(dis, productList); 
		RunTool(vm);
	}
	private static void RunTool(VendingMachine vm) 
	{
		String usr_input;
		String secondary_input; 
		boolean to_run = true; 
		vm.start();
		displayMessages();
		scanner = new Scanner(System.in);
		
		
		while (to_run)
		{	
			usr_input = scanner.nextLine();
			switch (usr_input) {
			
			case "1" : 
				System.out.println("Insert Money");
				 secondary_input = scanner.nextLine();
				 try 
				 {
					 vm.insertMoney(Float.parseFloat(secondary_input));
				 }
				 catch(Exception error)
				 {
					 vm.abort();
					 System.out.println("Wrong Input");
				 }
				break;	
			
			case "2" : 
				System.out.println("Please Enter Product Name");
				secondary_input = scanner.nextLine();
				vm.chooseProduct(secondary_input);
				break; 
			
			case "abort" : 
				vm.abort();
				break;
			
			case "prices" : 
				displayPricingList(vm.getProductsList());
				break; 
			
			case "Standby": 
				vm.end();
				break; 
			
			case "start" : 
				System.out.println("Starting tool");
				vm.start(); 
				break;
				
			case "exit" :
				System.out.println("Going to standby ");
				vm.end();
				to_run = false;
				
				break; 
			}
		}
	}
	
	private static void displayMessages() {
		System.out.println();
		System.out.println("- To Insert Money press 1 - "
							+"\n- To choose product press 2 - "
							+"\n- To abort please enter 'abort' - "
							+"\n- To Exit please enter exit"
							+"\n- To view products please enter prices - "
							+"\n- enter Standby to change tool to standby - "
							+"\n- enter start to start - ");
	}
	
	private static void displayPricingList(LinkedList<Product> products) {
		Iterator<Product> i = products.iterator();
		Product cur_product = null; 
		
		while(i.hasNext()) {
			cur_product = i.next(); 
			System.out.print(cur_product.getProductName() + "Price is :" + cur_product.getPrice());
		}
	}
	
	static LinkedList<Product> initProductList(){
		int i = 0; 
		Product[] products = {new Product(15, "Pickle"), 
							  new Product(4, "Cola"), 
							  new Product(5, "Chocolate"), 
							  new Product(2 ,"PopTart")};   											
		LinkedList<Product> productList = new LinkedList<Product>(); 
		
		for (int j = 0; j < products.length; j++) {
			productList.add(products[i]);
			++i;
		}
		
		return productList;
	}
}
