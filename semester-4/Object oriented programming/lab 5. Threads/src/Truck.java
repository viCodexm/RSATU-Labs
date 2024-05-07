import java.util.logging.Logger;

public class Truck extends Thread {
    private final Logger logger;
    private final Object lock;
    public String color;
    public float speed;

    Truck(Logger logger, Object lock) {
        this.logger = logger;
        this.lock = lock;
    }

    public void setColor(String color) {
        this.color = color;
    }

    @Override
    public void run() {
        int time = 0;
        while (true) {
            double distance = ++time * speed;
            System.out.println("Грузовая машина проехала: " + distance);

            if (distance >= 20.0 && distance < 30.0) {
                synchronized (lock) {
                    lock.notify();
                    logger.info("Грузовая машина отправила уведомление");
                }
            }

            if (distance >= 60.0) {
                logger.info("----Грузовая машина финишировала!----");
                break;
            }
            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}