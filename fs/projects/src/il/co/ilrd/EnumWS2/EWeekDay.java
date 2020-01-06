package il.co.ilrd.EnumWS2;

public enum EWeekDay {
		SUNDAY		,
	    MONDAY		, 
		TUESDAY		, 
		WEDNESDAY	, 
		THURSDAY	, 
		FRIDAY		, 
		SATURDAY	;
		
		
	static String fromValue(int indx) throws Exception{
		
		if (indx < 1 ||indx > 7)
		{
			throw new Exception("Invalid index");
		}
		
		EWeekDay[] days = EWeekDay.values();   
		return days[indx - 1].toString(); 
	}
	
	static void PrintDays() {
		EWeekDay[] days = EWeekDay.values();   
		for (EWeekDay day : days ) {
			System.out.println(day.toString());
		}
	}
	
	int dayValue() {
		
		return this.ordinal() + 1; 
	}
	
}

