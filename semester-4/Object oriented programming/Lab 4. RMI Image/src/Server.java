import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Server extends UnicastRemoteObject implements RMI {

    public Server() throws RemoteException {
        super();
    }

    public FileInputStream createFileInputStreamFromByteArray(byte[] fileData) throws IOException {
        File tempFile = File.createTempFile("temp", ".tmp");

        try (FileOutputStream fos = new FileOutputStream(tempFile)) {
            fos.write(fileData);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return new FileInputStream(tempFile);
    }

    @Override
    public void sendToServer(byte[] fileData) throws RemoteException {
        System.out.println("Client sent file for decoding.");
        System.out.println("Decode: ");
        String save_path = "/home/dmitry/Data/src/Git/RSATU-Labs/semester-4/Object oriented programming/Lab 4. RMI Image/src/";

        try {
            FileInputStream file = createFileInputStreamFromByteArray(fileData);

            CRLEDecoder decoder = new CRLEDecoder(file, save_path + "decoded-image.bmp");
            decoder.decodeFile();
        }
        catch (Exception e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws Exception {
        Registry rmiregistry = LocateRegistry.createRegistry(6000);
        rmiregistry.bind("server", new Server());
        System.out.println("RLE server is running...");
    }
}
