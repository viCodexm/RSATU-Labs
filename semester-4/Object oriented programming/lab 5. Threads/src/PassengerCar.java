import java.util.logging.Logger;

public class PassengerCar extends Car implements Runnable {
    private final Logger logger;
    private final Object lock;

    PassengerCar(Logger loger, Object lock) {
        this.logger = loger;
        this.lock = lock;
    }

    @Override
    void setColor(String color) {
        this.color = color;
    }

    @Override
    public void run() {
        int time = 0;

        synchronized (lock) {
            try {
                lock.wait();
                System.out.println("Легковая машина получила уведомление");
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }


        while (true) {
            double distance = ++time * speed;
            System.out.println("Легковая машина проехала: " + distance);

            if (distance >= 30.0 && distance < 40.0) {
                System.out.println("Легковая машина проехала больше 30км");
            }
            if (distance >= 50.0 && distance < 60.0) {
                System.out.println("Легковая машина проехала больше 50км");
            }

            if (distance >= 60.0) {
                logger.info("----Легковая машина финишировала!----");
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
