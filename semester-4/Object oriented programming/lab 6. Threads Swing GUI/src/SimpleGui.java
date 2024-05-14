import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import java.util.logging.Logger;

public class SimpleGui {
    private static final Logger logger = Logger.getLogger(SimpleGui.class.getName());
    private static final Object lock = new Object();
    JFrame frame;
    MyDrawPanel panel;
    JButton button1;
    JButton button2;
    PassengerCar2 sedan;
    Thread sedanThread;
    Truck2 truck;

    public static void main(String[] args) {
        SimpleGui gui = new SimpleGui();
        SwingUtilities.invokeLater(gui::setupWidjets);
    }

    public void setupWidjets() {
        frame = new JFrame();
        panel = new MyDrawPanel();
        button1 = new JButton("Стоп");
        button2 = new JButton("Старт");

        sedan = new PassengerCar2(logger, 24);
        truck = new Truck2(logger, 16);
        button1.addActionListener(new StopThreads());
        button2.addActionListener(new StartThreads());

        panel.add(button1);
        panel.add(button2);

        frame.getContentPane().add(BorderLayout.CENTER, panel);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(1000, 600);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        panel.setVisible(true);

        sedanThread = new Thread(sedan, "Sedan Thread");
        sedanThread.setPriority(3);
        truck.setPriority(2);
        sedanThread.start();
        truck.start();
    }

    class StopThreads implements ActionListener {
        public void actionPerformed(ActionEvent event) {
            sedan.setReady(false);
            truck.setReady(false);
            panel.repaint();
        }
    }

    class StartThreads implements ActionListener {
        public void actionPerformed(ActionEvent event) {
            sedan.setReady(true);
            truck.setReady(true);
            panel.repaint();
        }
    }

    public class MyDrawPanel extends JPanel {

        public void paintComponent(Graphics g) {
            g.setColor(Color.black);
            g.fillRect(0, 0, this.getWidth(), this.getHeight());

            g.setColor(Color.white);
            g.fillOval(sedan.x, sedan.y, 50, 50);

            g.setColor(Color.red);
            g.fillRect(truck.x, truck.y, 50, 50);
        }
    }



    public class Truck2 extends Thread {
        private final Logger logger;
        boolean ready;
        int x, y;
        int speed;

        Truck2(Logger logger, int speed) {
            this.logger = logger;
            this.speed = speed;
            x = 50; y = 150;
            ready = false;
        }

        void move() {
            x += speed;
        }

        public void setReady(boolean ready) {
            synchronized (this) {
                this.ready = ready;
                notify();
            }
        }

        @Override
        public void run() {
            System.out.println("Легковая машина запущена");

            while (true) {

                synchronized (this) {
                    while (!ready) {
                        try {
                            wait(); // Wait until notified
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }

                move(); panel.repaint();
                int distance = x - 50;
                System.out.println("Грузовая машина проехала: " + distance);

                if (distance >= 20 && distance < 30) {
                    synchronized (lock) {
                        lock.notify();
                        logger.info("Грузовая машина отправила уведомление");
                    }
                }

                if (distance >= 850) {
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



    public class PassengerCar2 extends Car implements Runnable {
        private final Logger logger;
        boolean ready;
        int x, y;

        PassengerCar2(Logger logger, int speed) {
            this.logger = logger;
            this.speed = speed;
            x = y = 50;
            ready = false;
        }

        void move() {
            x += speed;
        }

        public void setReady(boolean ready) {
            synchronized (this) {
                this.ready = ready;
                notify();
            }
        }

        @Override
        public void run() {
            System.out.println("Легковая машина запущена");

            while (true) {

                synchronized (this) {
                    while (!ready) {
                        try {
                            wait(); // Wait until notified
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }
                move(); panel.repaint();
                int distance = x - 50;
                System.out.println("Легковая машина проехала: " + distance);

                if (distance >= 30 && distance < 40) {
                    System.out.println("Легковая машина проехала больше 30км");
                }
                if (distance >= 50 && distance < 60) {
                    System.out.println("Легковая машина проехала больше 50км");
                }

                if (distance >= 850) {
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
}