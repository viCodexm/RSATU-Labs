
import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
public class ImageServer extends ImageCompressorRLE {
    public static void main(String[] args) {
        try {
            ImageCompressorRLE compressor = new ImageCompressorRLE();
            Registry registry = LocateRegistry.createRegistry(1099);
            Naming.rebind("rmi://localhost:1099/ImageCompressorService", (Remote) compressor);
            System.out.println("ImageCompressorServer is ready.");
        } catch (Exception e) {
            System.err.println("ImageCompressorServer exception: " + e.toString());
            e.printStackTrace();
        }
    }
}
