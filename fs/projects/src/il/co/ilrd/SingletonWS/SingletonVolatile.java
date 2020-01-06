package il.co.ilrd.SingletonWS;

public class SingletonVolatile {
    private volatile static SingletonVolatile instance;
    private SingletonVolatile (){}
 
    public static SingletonVolatile getSingleton() {
        if (instance == null) {                         
            synchronized (SingletonVolatile.class) {
                if (instance == null) {       
                    instance = new SingletonVolatile();
                }
            }
        }
        return instance;
    }
}
