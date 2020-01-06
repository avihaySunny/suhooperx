package audioFactory;

import java.util.function.Function;

public class AudioFactory<T>{

	
	public static void main(String[] args) {
		GenericFactory<AudioWave, String, Integer> waveFactory = new GenericFactory<>();  
		
	
		
		Function<Integer, ? extends AudioWave > squareWaveCreator = new Function<Integer, AudioWave>() {
 
			public AudioWave apply(Integer t) {
				return new SquareWave(t.intValue()); 
			}
			
		};
		
		Function<Integer, ? extends AudioWave> creatie  = (a)->  {return new SineWave(a);}; 
		
		waveFactory.addClass("SineWave", creatie);
		waveFactory.addClass("SquareWave", squareWaveCreator);
		
		
		
		
		
		SquareWave mywave = new SquareWave(50); 
		
		waveFactory.addClass("squarey", mywave.apply(100));
		
		
		waveFactory.addClass("siney", SineWave::new);
		
		System.out.println(waveFactory.create("siney", 30).getClass());
		
		waveFactory.addClass("squarush", SquareWave::new);
		System.out.println(waveFactory.create("squarush", 30).getClass());
		
		waveFactory.addClass("sw", squareWaveCreator::apply);
		System.out.println(waveFactory.create("sw", 30).getClass());
	}		
}
