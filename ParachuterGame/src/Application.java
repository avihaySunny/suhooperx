
import javax.swing.JFrame;
import javax.swing.UIManager;

public class Application extends JFrame {
	private static final long serialVersionUID = 1L;

	public Application() throws Exception{
      
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

    public void startGame() throws Exception {
    	initUI(); 
    	this.setVisible(true);
    }
}
