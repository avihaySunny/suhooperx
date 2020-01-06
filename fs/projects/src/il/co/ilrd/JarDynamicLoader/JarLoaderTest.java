package il.co.ilrd.JarDynamicLoader;

public class JarLoaderTest {

	public static void main(String[] args) {
		
		String path_initial = System.getProperty("user.dir");
		String path_to_jar = new String(path_initial + "/src/il/co/ilrd/JarDynamicLoader/LibFile.jar");
		Class<?>[] foundCLasses = null; 
		JarDynamicLoader loader = new JarDynamicLoader(path_to_jar, "actions");
		try {
			foundCLasses = loader.load(); 
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		
		for (Class<?> c : foundCLasses) {
			System.out.println(c.getName());
		}
		
	}
}

