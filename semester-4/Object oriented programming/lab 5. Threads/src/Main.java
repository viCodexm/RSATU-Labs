import java.util.logging.Logger;
import java.util.logging.FileHandler;
import java.util.logging.SimpleFormatter;

public class Main {
    private static final Logger logger = Logger.getLogger(Main.class.getName());
    private static final Object lock = new Object();

    public static void main(String[] args) {
        try {
            FileHandler fh = new FileHandler("car_movement.log", true);
            fh.setFormatter(new SimpleFormatter());
            logger.addHandler(fh);
        } catch (Exception e) {
            e.printStackTrace();
        }

        PassengerCar sedan = new PassengerCar(logger, lock);
        Truck truck = new Truck(logger, lock);

        sedan.setColor("Blue");
        truck.setColor("Black");
        sedan.speed = 10;
        truck.speed = 8;

        Thread sedanThread = new Thread(sedan, "Sedan Thread");
        truck.setName("Truck Thread");

        sedanThread.setPriority(3);
        truck.setPriority(2);

        logger.info("Car movement started");

        sedanThread.start();
        truck.start();

        try {
            sedanThread.join();
            truck.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}