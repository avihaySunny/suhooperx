import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Toolkit;
import javax.swing.Timer;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.Random;
import java.util.concurrent.Semaphore;
import javax.swing.JPanel;

/*
 * Written by Avihay Asraf, November 19 
 * this module implements the game logic, 
 * manages game resources (images, sounds, timer and threads) and handles user 
 * input  
 */
public class GameEngine extends JPanel implements Config{ 
	private static final long serialVersionUID = 1L;
	
	private GameStaticComponent background = new GameStaticComponent("src/resources/images/background.png");; 
	private GameStaticComponent sea		 = new GameStaticComponent("src/resources/images/sea.png");  
	private GameStaticComponent gameOver   = new GameStaticComponent("src/resources/images/gameover.jpg"); 
	private GameStaticComponent startGame  = new GameStaticComponent("src/resources/images/startscreen.jpg"); 

	private Airplane plane 	      = new Airplane ("src/resources/images/plane.png"); 
	private Boat boat			  = new Boat("src/resources/images/boat.png"); 
	private Parachuter parachuter = new Parachuter("src/resources/images/parachutist.png");
	
	private int score = 0;
	private int lives = INITIAL_HP; 
	
	/*
	 * responsible for holding thread
	 * from dropping chute too early  
	 */
	private Semaphore dropLock = new Semaphore(0); 
	private boolean waitOnStart = true; 
	
	//swing timers for updating graphics 
	// moves boats 
	private Timer boatMovementTimer = new Timer(KEY_PRESS_INTERVAL, (s)-> {
		stepBoat(); 
	;});  
	
	// moves plane at constant speed
	private Timer planeMomventTimer = new Timer(PLANE_ANIMATION_INTERVAL, (s) -> { 
		stepPlane(); 
	;});
	
	// moves parachuter 
	private Timer parachuteMovmentTimer = new Timer(PARACHUTER_ANIM_DELAY , (s) -> { 
		if (parachuter.getFalling()) {
			dropChute();
			parachuter.setX(plane.getXPos());
		}
	;}); 
	
	//checks and stops game if game has ended
	private Timer moniterGame = new Timer(MONITER_RATE , (s) -> { 
		if (lives == 0)
			stopGame();
	;}); 
	
		// play theme music in repeat unless game has ended
	private Thread themeMusicPlayer = new Thread(() -> { 
		boolean play = true; 	
		while (play) {
					Sound.play("src/resources/sounds/themesong.wav");
				try {
					Thread.sleep(THEME_SOUND_LENTGH);
				}catch(Exception e) {
					if (lives == 0) {
						play = false; 
					}
				}
			}
	;}); 
	
	//responsible for dropping chute randomly 
	private Thread randomDropReset = new Thread(()-> {		
			while(lives > 0) {
				//clamp so parachuter will drop between borders 
				parachuter.setX(clamp(plane.getXPos(), CLAMP_X_MIN, CLAMP_X_MAX));
				parachuter.setFalling(true);
				
				try {
					dropLock.acquire(); 
					// random sleep for random drop
					Thread.sleep(Math.abs(new Random().nextLong() % SLEEP_MILI));
				} catch (InterruptedException e) { 
					e.printStackTrace();
				}
			}
		});
						
	/*------- class for key presses event -------------------------------------------------------------------------------*/ 
	private class TAdapter extends KeyAdapter {
		@Override
	    public void keyReleased(KeyEvent e) {
	        boat.whenKeyRelease(e);
	        whenKeyPress(e);
	    }

	    @Override
	    public void keyPressed(KeyEvent e) {
	        boat.whenKeyPress(e);
	    }
	}
	/*------------------------------------------------------------------------------------------------------------------*/
	public GameEngine() {
		addKeyListener(new TAdapter());
		setFocusable(true);
		themeMusicPlayer.start();
	}
	
	@Override
	public void paintComponent(Graphics g) {
		g.setFont(new Font(FONT, FONT_STYLE, FONT_SIZE));
	    super.paintComponent(g);
    	doDrawing(g);
        Toolkit.getDefaultToolkit().sync();
    }
	    
    private void doDrawing(Graphics g) {
    	Graphics2D g2d = (Graphics2D) g;
    		//start screen 
    	if (waitOnStart) {
    		g2d.drawImage(startGame.getIm(), null, null);
    	}
    		//main game screen rendering 
    	else if (lives > 0 && !waitOnStart) {
	        g2d.drawImage(background.getIm(), null, null); 
	        g2d.drawImage(sea.getIm(), SEA_POS_X, SEA_POS_Y, sea.getWidth(), sea.getHeight(), this); 
	        g2d.drawImage(plane.getIm(), plane.getXPos(), plane.getYPos(), this);
	        g2d.drawImage(boat.getIm(), boat.getXPos(), boat.getYPos(), this); 
	       
	        // if parachute is falling it will not appear on screen 
	        if(parachuter.getFalling() == true) {
	        	g2d.drawImage(parachuter.getIm(), parachuter.getXPos() + BORDER_EXTRA_2, parachuter.getYPos() + BORDER_EXTRA_1,this);  
	        }
	        
	        // game states  
	        g.drawString("SCORE :" + score ,TEXT_POS_X ,TEXT_POS_Y_UPPER);
	        g.drawString("LIVES :" + lives ,TEXT_POS_X ,TEXT_POS_Y_LOWER); 
	    	
    	}
        else 
        	g2d.drawImage(gameOver.getIm(), null, null);
    }
    	// move according to key press and repaint the appropriate area 
	private void stepBoat() {
		boat.move();
		repaint(boat.getXPos() - BORDER_EXTRA_1 , boat.getYPos() - BORDER_EXTRA_1 , 
				boat.getWidth()+ BORDER_EXTRA_1, boat.getHeight() + BORDER_EXTRA_1); 
	}
	
		// constant plane movement and repainting 
	private void stepPlane() {
		plane.move(); 
		repaint(plane.getXPos() , plane.getYPos() , plane.getWidth() + PLANE_BORDER_EXTRA, plane.getHeight());
	}
		// stops waiting in start-game screen
	private void promptEnterKey(){
		waitOnStart = false; 
		repaint();
	}
	
	private int clamp(int x, int min, int max) {
		return Math.max(min,Math.min(max, x));
	}
		// start running all game threads
	private void startGameThreads() {
		boatMovementTimer.start();
		planeMomventTimer.start();
		parachuteMovmentTimer.start();
		moniterGame.start();
		randomDropReset.start();		
	}
		/*
		 * drops chute at const speed, repaints 
		 * resets the chute when reaches the limit of y axis 
		 * posts on lock so drop chute thread can continue 
		 * play sounds using the Sound class 
		 */
	private void dropChute() {
		parachuter.move();
		repaint();
		
		if (parachuter.getYPos() >= PARACHUTER_LIMIT_Y) {
			parachuter.setFalling(false);
			
			if (CheckCollision()){
				//play happy sound
				Sound.play("src/resources/sounds/yipee.wav");
				score += 10 ; 
			}
			else {
				//play sad 
				Sound.play("src/resources/sounds/drowning.wav");
				--lives; 
			}
			parachuter.resetYPos();
			dropLock.release();
		}
	}

	/*
	 * returns true if one image overlaps 
	 * another by checking border intersection
	 */
	private boolean CheckCollision() {
		return boat.getBorders().intersects(parachuter.getBorders());
	}
	
	private void stopGame() {
		parachuteMovmentTimer.stop();
		planeMomventTimer.stop();
		boatMovementTimer.stop();
		moniterGame.stop();
		themeMusicPlayer.interrupt();
		Sound.stopSounds(); 
		
	}

	private void whenKeyPress(KeyEvent keyPress) {
		if(keyPress.getKeyCode() == KeyEvent.VK_ENTER) {
			promptEnterKey();
			startGameThreads();
		}
	}
}