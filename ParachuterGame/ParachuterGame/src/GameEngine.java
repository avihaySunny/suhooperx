import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Toolkit;
import javax.swing.Timer;

import resources.GameComponent;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.File;
import java.util.Random;
import java.util.concurrent.Semaphore;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class GameEngine extends JPanel { 
	private static final long serialVersionUID = 1L;
	/*
	 * swing timers 
	 * update state for drawing
	 */
	private Timer boatMovementTimer; 
	private Timer planeMomventTimer; 
	private Timer parachuteMovmentTimer;
	private Timer moniterGame; 
	
	//game resources
	private GameComponent background; 
	private GameComponent sea; 
	private GameComponent gameOver; 
	private GameComponent startGame; 
	
	private Plane plane; 
	private Boat boat; 
	private Parachuter parachuter;
	
	private int score;
	private int lives = Config.INITIAL_HP; 
	
	/*
	 * responsible for holding thread
	 * from dropping chute too early  
	 */
	private Semaphore dropLock; 
	private boolean waitOnStart = true; 
	
	/*
	 * thread responsible for 
	 * resetting the 
	 */
	private Thread randomDropReset = new Thread(()->{
			 //sleep so first parachuter won't drop too early
			try {
					Thread.sleep(2000);
			} catch (InterruptedException e1) {}
			
			while(lives > 0) {
				parachuter.setX(clamp(plane.getXPos()));
				parachuter.setFalling(true);
				
				try {
					dropLock.acquire(); 
					/*
					 * the random element of
					 * dropping chute 
					 */
					Thread.sleep(Math.abs(new Random().nextLong() % 2000));
				} catch (InterruptedException e) { 
					e.printStackTrace();
				}
			}
		});

	public GameEngine() {
		initBoard(); 
	}
	
	private void initBoard() { 
		addKeyListener(new TAdapter());
		setFocusable(true);
		dropLock = new Semaphore(0);
		
		startGame = new GameComponent("src/resources/startscreen.jpg");
		gameOver = new GameComponent("src/resources/gameover.jpg");
		background = new GameComponent("src/resources/background.png"); 
		sea = new GameComponent("src/resources/sea.png");  
		
		boat = new Boat("src/resources/boat.png"); 
		plane = new Plane("src/resources/plane.png");  
		parachuter = new Parachuter("src/resources/parachutist.png");
		 
		
		/*
		 * moves and repaints boats 
		 */
		boatMovementTimer = new Timer(Config.KEY_PRESS_DELAY, (s)->{
			stepBoat(); 
		;}); 
		
		/*
		 * moves plane at constant speed
		 */
		planeMomventTimer = new Timer(Config.PLANE_ANIMATION_DELAY, (s) -> { 
			stepPlane(); 
		
		;}); 
		/*
		 * moves chute when falling
		 */
		parachuteMovmentTimer = new Timer(Config.PARACHUTER_ANIM_DELAY , (s) -> { 
			if (parachuter.getFalling())
				dropChute();
		;}); 
		
		/*
		 * stops game thread in case it's over
		 */
		moniterGame = new Timer(Config.MONITER_RATE, (s) -> { 
			if (lives == 0)
				stopGame();
		;}); 
		
		new Thread(()->{
			promptEnterKey(); 
			startGameThreads(); 
		
			;}).start(); 
	}
	 
	@Override
	public void paintComponent(Graphics g) {
	    super.paintComponent(g);
    	doDrawing(g);
        Toolkit.getDefaultToolkit().sync();
    }
	    
    private void doDrawing(Graphics g) {
    	Graphics2D g2d = (Graphics2D) g;
    	if (waitOnStart) {
    		g2d.drawImage(startGame.getIm(), null, null);
    	}
    	else if (lives > 0 && !waitOnStart) {
	        g2d.drawImage(background.getIm(), null, null); 
	        g2d.drawImage(sea.getIm(), Config.SEA_POS_X, Config.SEA_POS_Y, sea.getWidth(), sea.getHeight(), this); 
	        g2d.drawImage(plane.getIm(), plane.getXPos(), plane.getYPos(), this);
	        g2d.drawImage(boat.getIm(), boat.getXPos(), boat.getYPos(), this); 
	       
	        if(parachuter.getFalling() == true) {
	        	g2d.drawImage(parachuter.getIm(), parachuter.getXPos() + 1, parachuter.getYPos() +1,this);  
	        }
	        
	        g.drawString("SCORE :" + score , 10 , 25);
	        g.drawString("LIVES :" + lives, 10, 50); 
	    	}
        else 
        	g2d.drawImage(gameOver.getIm(), null, null);

    }

	private void stepBoat() {
		boat.move();
		repaint(boat.getXPos() - 2 , boat.getYPos() - 2, boat.getWidth()+3, boat.getHeight() + 2); 
	}
	
	private void promptEnterKey(){
		JOptionPane.showMessageDialog(null, "press enter"); 
		waitOnStart = false; 
		repaint();
	}
	
	private int clamp(int x) {
		return Math.max(Config.CLAMP_X_MIN, Math.min(Config.CLAMP_X_MAX, x));
	}
	
	private void startGameThreads() {
		boatMovementTimer.start();
		planeMomventTimer.start();
		parachuteMovmentTimer.start();
		moniterGame.start();
		randomDropReset.start();	
		
	}
	
	private void stepPlane() {
		plane.move(); 
		repaint(plane.getXPos() , plane.getYPos() , plane.getWidth() + 15, plane.getHeight());
	}
	
	private void dropChute() {
		parachuter.move();
		repaint();
		
		if (parachuter.getYPos() >= Config.PARACHUTER_LIMIT_Y) {
			parachuter.setFalling(false);
			
			if (CheckCollision()){
				//play happy sound
				Sound.play("src/resources/yipee.wav");
				score += 10; 
			}
			else {
				//play sad 
				Sound.play("src/resources/drowning.wav");
				--lives; 
			}
			parachuter.resetYPos();
			dropLock.release();
		}
	}

	private boolean CheckCollision() {
		return boat.getBorders().intersects(parachuter.getBorders());
	}
	
	
	private void stopGame() {
		parachuteMovmentTimer.stop();
		planeMomventTimer.stop();
		boatMovementTimer.stop();
		moniterGame.stop();
	}
	
	private static class Sound {
	    private static synchronized void play(final String fileName) 
	    {            
	        new Thread(()-> { 
                try {
                    Clip clip = AudioSystem.getClip();
                    AudioInputStream inputStream = AudioSystem.getAudioInputStream(new File(fileName));
                    clip.open(inputStream);
                    clip.start(); 
                } catch (Exception e) {
                    System.out.println("play sound error: " + e.getMessage() + " for " + fileName);
                }
	        }).start();
	    }
	}

	private class TAdapter extends KeyAdapter {

	    @Override
	    public void keyReleased(KeyEvent e) {
	        boat.whenKeyRelease(e);
	    }

	    @Override
	    public void keyPressed(KeyEvent e) {
	        boat.whenKeyPress(e);;
	    }
	}
}
