import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.net.MalformedURLException;
import java.rmi.NotBoundException;

public class CalculatorClient {
    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            Calculator c = (Calculator) Naming.lookup("rmi://localhost/CalculatorService");

//            System.out.println( c.sub(4, 3) );
//            System.out.println( c.add(4, 10) );
//            System.out.println( c.mul(3, 6) );
//            System.out.println( c.div(9, 3) );
        }
        catch (MalformedURLException murle) {
            System.out.println("\nMalformedURLException");
            System.out.println(murle);
        }
        catch (RemoteException re) {
            System.out.println("\nRemoteException");
            System.out.println(re);
        }
        catch (NotBoundException nbe) {
            System.out.println("\nNotBoundException");
            System.out.println(nbe);
        }
        catch (java.lang.ArithmeticException ae) {
            System.out.println("\njava.lang.ArithmeticException");
            System.out.println(ae);
        }
    }

}
