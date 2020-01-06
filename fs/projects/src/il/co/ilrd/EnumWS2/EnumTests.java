package il.co.ilrd.EnumWS2;

public class EnumTests {
	
	public static void main(String[] args) {

		try{
				System.out.println(EWeekDay.fromValue(5));
			}
		catch (Exception e ){
				System.out.println(e.getMessage());
			}
		
		EWeekDay.PrintDays();
		System.out.println(EWeekDay.THURSDAY.dayValue());
	}	
		
}

