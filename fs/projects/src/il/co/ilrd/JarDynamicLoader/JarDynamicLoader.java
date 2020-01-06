package il.co.ilrd.JarDynamicLoader;
import java.io.IOException;
import java.util.Enumeration;
import java.util.LinkedList;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

public class JarDynamicLoader {
	private String path;
	private String interfaceName; 
	private String packageName; 
	
	public JarDynamicLoader(String path, String interfaceName) {
		this.path = path; 
		this.interfaceName = interfaceName;
	}
	
	private JarFile loadJarFile() throws IOException{
		JarFile myLib = null; 
		myLib = new JarFile(path); 
		
		return myLib;
	}
		
	public Class<?>[] load(){
		JarFile myLib = null; 
		Enumeration<JarEntry> entries = null; 
		Class[] foundClasses = null; 
		try {
			myLib = loadJarFile();
			entries = myLib.entries();
			setPackageName(entries);
			foundClasses =  classFromEntries(entries);
			myLib.close();
		
		}catch (Exception e) {}
		
		return foundClasses;
	}

	private void setPackageName(Enumeration<JarEntry> entries){
		entries.nextElement();
		JarEntry cur_entry = entries.nextElement();
		int position = cur_entry.getName().indexOf('/');
		this.packageName = new String(cur_entry.getName().substring(0,position) +"."); 
	}
	
	private Class<?>[] classFromEntries(Enumeration<JarEntry> entries){
		LinkedList <Class<?>> classList = new LinkedList<Class<?>>(); 
		ClassLoader classLoader = new ClassLoader(){};
		JarEntry cur_entry = null; 
		Class<?> cur_class = null; 
		
		do {
			cur_entry = entries.nextElement();
			if(cur_entry.isDirectory() || !cur_entry.getName().endsWith(".class")){
                continue;
            }
		
			String className = cur_entry.getName().substring(0 ,cur_entry.getName().length() - 6);
            String fullClassName = new String(className.replace('/', '.'));
            
            try {
            	cur_class = classLoader.loadClass(fullClassName);
            	Class<?>[] interfaces = cur_class.getInterfaces();
            	for (Class<?> current : interfaces) {
            		if (current.getName().equals(packageName + interfaceName)) 
            		{
            			classList.add(cur_class);
            			break; 
            		}
            	}		
			}
            catch (ClassNotFoundException e){}
           
		}while (entries.hasMoreElements());
		
		return classList.toArray(new Class[classList.size()]);
	}	
}