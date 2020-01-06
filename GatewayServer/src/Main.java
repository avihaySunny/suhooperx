
import java.io.IOException;

//import GatewayHttpServer.CommandFactory;

public class Main {
	public static void main(String[] args) throws IOException {
		var gwServer = new GatewayHttpServer(8500); 
		gwServer.startServer();
	}
}
