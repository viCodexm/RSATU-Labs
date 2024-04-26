
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ImageCompressor extends Remote {
    void compress(long a) throws RemoteException;
}
class ImageCompressorRLE implements ImageCompressor {
    public void compress(long a) throws java.rmi.RemoteException {
        System.out.println("Сжатие картинки");
    }
}
