import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.UIManager;

public class Application extends JFrame {
	private static final long serialVersionUID = 1L;

	public Application() throws Exception{

        initUI();
    }
	
    private void initUI() throws Exception {
    	UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        add(new GameEngine());
        setTitle("ParachuterGame");
        setSize(1080, 720);
        setLocationRelativeTo(null);
        setResizable(false); 
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       
    }  

    public static void main(String[] args) throws Exception {
        EventQueue.invokeLater(() -> {
            Application game;
			try {
				game = new Application();
				game.setVisible(true);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
  
        });
    }
}
