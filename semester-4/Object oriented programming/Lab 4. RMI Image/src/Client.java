import java.io.File;
import java.nio.file.Files;
import java.rmi.Naming;
import java.util.Scanner;

public class Client {

    static Scanner input = null;

    public static void main(String[] args) throws Exception {
        RMI chatapi = (RMI) Naming.lookup("rmi://localhost:6000/server");
        input = new Scanner(System.in);

        System.out.println("Connected to server...");
        String image_path = "/home/dmitry/Data/src/Git/RSATU-Labs/semester-4/Object oriented programming/Lab 4. RMI Image/src/rgb";


        try {
            System.out.println("Encode: ");
            CRLEEncoder encoder = new CRLEEncoder(image_path + ".bmp", image_path + ".compressed-bmp");
            encoder.encodeFile();

            File file = new File(image_path + ".compressed-bmp");
            byte[] fileData = Files.readAllBytes(file.toPath());
            chatapi.sendToServer(fileData);
        }
        catch (Exception e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        System.out.println("Done.");
    }
}