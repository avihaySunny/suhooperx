package audioFactory;
import java.lang.Math;
import java.util.function.Function; 

abstract class AudioWave {
	static final int SCALEFACTOR = 250;
	double[] amplitude; 
	public void printWave() {} 
	public int rms() {return 0;} 
	
}
	
class SquareWave extends AudioWave implements Function<Integer ,SquareWave> {	
	
	public SquareWave(int sampleNum) {
		amplitude = new double[sampleNum]; 
		for (int i = 0; i < amplitude.length ; i+=2) {
			if (i % 2 == 0) {
				amplitude[i] = 1; 
				amplitude[i+1] = 1;
			}
		}
	}
	
	Function<Integer, ? extends SquareWave> SquareWaveCreator = new Function<Integer, SquareWave>() {

		@Override
		public SquareWave apply(Integer t) {
			// TODO Auto-generated method stub
			return null;
		}
		
	};

	@Override
	public SquareWave apply(Integer t) {
		return new SquareWave(t);
	}

}
	
class SineWave extends AudioWave {

	public SineWave(int sampleNum) {
		double radians; 
		double dt = 2* Math.PI / sampleNum;  
		amplitude = new double[sampleNum]; 
		for (int i = 0; i < sampleNum; ++i) {
			radians = (Math.PI / SCALEFACTOR) * i;
			amplitude[i] = Math.sin(radians);
		}
	}
	
	
		
}

