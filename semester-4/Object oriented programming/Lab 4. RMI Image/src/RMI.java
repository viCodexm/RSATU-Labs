import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMI extends Remote {
    void sendToServer(byte[] fileData) throws RemoteException;
}