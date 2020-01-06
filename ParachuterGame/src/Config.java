/*
 * Written by Avihay Asraf, Nov 19 
 * this file hold all game values and constants 
 * except for 0 
 */
public interface Config {
	// timer interval for key press check
	final static int KEY_PRESS_INTERVAL = 10; 
	
	// timer interval for drawing plane motion
	final static int PLANE_ANIMATION_INTERVAL = 15; 
	
	//edge of window (pixels) 
	final static int X_BORDER_LIMIT = 1080; 
	
	// reset point for parachuter 
	final static int PARACHUTER_LIMIT_Y = 520;  
	
 	// timer interval for parachuter movement
	final static int PARACHUTER_ANIM_DELAY  = 20; 
	final static int INITIAL_HP = 3; 
	
	// start locations for sea 
	final static int SEA_POS_Y = 478; 
	final static int SEA_POS_X = 0;
	
	// time interval for checking if game has ended 
	final static int MONITER_RATE = 500; 
	
	final static int PARACHUTER_START_X = 50; 
	final static int PARACHUTER_START_Y = 50;
	final static int PARACHUTE_DROP_SPEED = 4; 
	
	final static int BOAT_START_X =  640; 
	final static int BOAT_START_Y = 500; 
	final static int BOAT_SPEED = 3; 
	
	final static int PLANE_SPEED = -3; 
	final static int PLANE_Y_POS = 30;
	final static int PLANE_START_X = 1080;	
	final static int CLAMP_X_MIN = 50; 
	final static int CLAMP_X_MAX = 1030;
	
	// locations for string displayed on screen 
	final static int TEXT_POS_X = 10; 
	final static int TEXT_POS_Y_UPPER = 25;
	final static int TEXT_POS_Y_LOWER = 50;
	
	// the above String font attributes 
	final static int FONT_SIZE = 20;
	final static int FONT_STYLE = 1; 
	String FONT = "Courier"; 
	
	// used in repaint so the picture will not drag on screen 
	final static int BORDER_EXTRA_1 = 3;  
	final static int BORDER_EXTRA_2 = 1; 
	final static int PLANE_BORDER_EXTRA = 15;
	// thread constants 
	final static int SLEEP_MILI = 2000; 
	final static int THREAD_COUNT = 1; 
	final static int PLAY_SOUNDS_RATE = 1000; 
	final static int THEME_SOUND_LENTGH = 18000; 
	
}

