package il.co.ilrd.SingletonWS;

public class HolderIdiom {
       
	private HolderIdiom() {}
		private static class SingletonHolder {
			public static HolderIdiom instance = new HolderIdiom();
			
			
	    }
	 
	    public static HolderIdiom getInstance() {
	        return SingletonHolder.instance;
	    }
}