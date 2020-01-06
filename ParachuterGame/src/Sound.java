import java.io.File;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;

// plays sounds using thread pool 
public class Sound {
	private static ExecutorService executor = Executors.newFixedThreadPool(Config.THREAD_COUNT);
	private static void playSound(String fileName) {
		try {
                Clip clip = AudioSystem.getClip();
                AudioInputStream inputStream = AudioSystem.getAudioInputStream(new File(fileName));
                clip.open(inputStream);
                clip.start(); 
     
		} catch (Exception e) {}
	}
	
	public static void play(String filename) {
		executor.execute(()-> {
			playSound(filename); 	
		});
	}
	
	public static void stopSounds() {
		executor.shutdownNow(); 
	}
}