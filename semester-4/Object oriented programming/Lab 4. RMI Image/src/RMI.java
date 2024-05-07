import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMI extends Remote {
    public void sendToServer(String message) throws RemoteException;
}