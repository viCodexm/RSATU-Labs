import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.net.MalformedURLException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class ImageClient {
    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            ImageCompressor compressor = (ImageCompressor) Naming.lookup("rmi://localhost:1099/ImageCompressorService");
            compressor.compress(1);

            // Загрузка изображения в байтовый массив
            //byte[] imageData = loadImageData("star.bmp");
            //byte[] compressedData = compressor.compressRLE(imageData);
            // Здесь можно сохранить сжатые данные в файл или выполнить другие действия

            //saveCompressedImage(compressedData, "compressed_image.bmp");
        } catch (MalformedURLException | NotBoundException | RemoteException e) {
            e.printStackTrace();
        }
    }
    // Метод для загрузки изображения в байтовый массив
    private static byte[] loadImageData(String imagePath) {
        try {
            Path path = Paths.get(imagePath);
            return Files.readAllBytes(path);
        } catch (IOException e) {
            e.printStackTrace();
            return new byte[0]; // Возвращаем пустой массив в случае ошибки
        }
    }
    private static void saveCompressedImage(byte[] compressedData, String outputPath) {
        try {
            Path path = Paths.get(outputPath);
            Files.write(path, compressedData);
            System.out.println("Сжатое изображение успешно сохранено в " + outputPath);
        } catch (IOException e) {
            e.printStackTrace();
            System.err.println("Ошибка при сохранении сжатого изображения.");
        }
    }

}
