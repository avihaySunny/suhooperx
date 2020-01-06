package il.co.ilrd.VendingMachine;
import java.util.*;
import com.sun.jmx.snmp.Timestamp;


public class VendingMachine {
    private float money;
    private StateVM state;
    private LinkedList<Product> productList;  
    private Display display;
    private Timer timerThread; 
    private long lastTimeStamp;
    
    public VendingMachine(Display display, LinkedList<Product> productList) 
    {
    	this.display = display;
    	this.productList = productList; 
    	changeState(StateVM.IDLE);
    }
    //---------------------------------------------------------------------------
    public void insertMoney(float amount)
    {
    	state.insertMoney(this, amount);
    }
    //--------------------------------------------------------------------------
    public LinkedList<Product> getProductsList(){
    	return productList; 
    }
    //---------------------------------------------------------------------------
    private class CheckTimeStamp extends TimerTask {
    	VendingMachine vm; 
    	CheckTimeStamp(VendingMachine vm){
    		this.vm = vm; 
    	}
   		@Override
        public void run() {
            vm.state.timeout(vm);
        }
   	}
    //---------------------------------------------------------------------------
    public void start() 
    {
    	final int delay = 1000; 
    	final int period = 1000;		
    	state.start(this);
    	if (timerThread == null){
    		timerThread = new Timer();
    		}
    	timerThread.scheduleAtFixedRate(new CheckTimeStamp(this), delay , period);
    }
    //---------------------------------------------------------------------------
    public void end() 
    {
    	if (timerThread != null) {
    		timerThread.cancel();
    		timerThread = null; 
    		state.end(this);
    	}
    }
    //---------------------------------------------------------------------------
    public void chooseProduct(String productName) 
    {
    	this.state.chooseProduct(this, productName);
    }
    //---------------------------------------------------------------------------
    public void abort() 
    {
    	state.abort(this);
    }
    //---------------------------------------------------------------------------
    void chooseProduct(VendingMachine vm, String productName)
    {
    	state.chooseProduct(vm, productName);
    }
    //---------------------------------------------------------------------------
    public void start(VendingMachine vm) {
    	state.start(this);
    }
    //---------------------------------------------------------------------------
    public void end(VendingMachine vm) {
    	state.end(this);
    }
    private void changeState(StateVM state) {
    	this.state = state;
    	lastTimeStamp = new Timestamp().getDateTime();
    }
   //--------------------------------------------- ENUM----------------------------------------------     
    private enum StateVM {
        NOT_READY
        {
            @Override
            void abort(VendingMachine vm) {}  
            
            void insertMoney(VendingMachine vm, float amount){
            	vm.money = amount; 
            	returnChange(vm);
            	
            }
            void start(VendingMachine vm) {
            	vm.changeState(IDLE);
            }
        },
        //-------------------------------------------------------------------------------------------
        IDLE
        {
            @Override
            void abort(VendingMachine vm) 
            {
            	vm.changeState(IDLE); 
            }
        },
      //-------------------------------------------------------------------------------------------
        COLLECTING_MONEY
        {	
        	int timeoutThreshold = 15000; 
        	void timeout(VendingMachine vm)
        	{
        		if ((new Timestamp().getDateTime() - vm.lastTimeStamp) > timeoutThreshold){
        			returnChange(vm); 
        			vm.changeState(IDLE);
        		}
        	}     	
            @Override
            void abort(VendingMachine vm)
            {
            	returnChange(vm); 
            	vm.changeState(IDLE);
            }
          //-------------------------------------------------------------------------------------------
            void chooseProduct(VendingMachine vm, String productName)
            { 
            	Product selectedProduct = FindInList(productName, vm.productList); 
	            if (selectedProduct.getProductName().equals(productName) && vm.money > selectedProduct.getPrice()) {
	            		vm.money -= selectedProduct.getPrice();
	            		vm.display.printToDisplay("HERE IS YOUR "+ productName );
	            } 
            	else {
	            		System.out.println("No Product / Not enough money");
        		}
	            	
            	vm.state.abort(vm);
            }
          //-------------------------------------------------------------------------------------------	
        	private Product FindInList(String productName, List<Product> product_list) 
        	{
        		Iterator <Product> i = product_list.iterator();
        		Product cur_product = null; 
        		
        		while(i.hasNext()) {
        			cur_product = i.next(); 
        			if (cur_product.getProductName().equals(productName)){
        				break; 
        			}
        		}
    			return cur_product; 
        	}
        }; 
    	//-------------------------------------------------------------------------------------------
        abstract void abort(VendingMachine vm);
        
        void chooseProduct(VendingMachine vm, String productName) {}
      //-------------------------------------------------------------------------------------------
        void start(VendingMachine vm){}
      //-------------------------------------------------------------------------------------------
        void end(VendingMachine vm){
        	returnChange(vm);
        	vm.changeState(NOT_READY);
        }
      //-------------------------------------------------------------------------------------------
        void returnChange(VendingMachine vm) {
        	vm.display.printToDisplay("Change is " + vm.money);
        	vm.money = 0; 
        }
      //-------------------------------------------------------------------------------------------
        void insertMoney(VendingMachine vm, float amount){
        	vm.money += amount; 
        	vm.changeState(COLLECTING_MONEY);
        }
      //------------------------------------------------------------------------------------------- 
        void timeout(VendingMachine vm){}
	};
}
