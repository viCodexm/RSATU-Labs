
import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
public class CalculatorServer {
    public CalculatorServer() {
        try {
            Calculator c = new Calculator.CalculatorImpl();
            Naming.rebind("rmi://localhost:1099/CalculatorService", (Remote) c);
        } catch (Exception e) {
            System.out.println("Trouble: " + e);
        }
    }
    public static void main(String[] args) throws RemoteException {
        final Registry registry = LocateRegistry.createRegistry(1099);

        CalculatorServer server = new CalculatorServer();
    }

}
