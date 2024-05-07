import java.rmi.Naming;
import java.util.Scanner;

public class Client {

    static Scanner input = null;

    public static void main(String[] args) throws Exception {
        RMI chatapi = (RMI) Naming.lookup("rmi://localhost:6000/chat");
        input = new Scanner(System.in);
        System.out.println("Connected to server...");
        System.out.println("Type a message for sending to server...");
        String message = input.nextLine();
        while(!message.equals("Bye")) {
            chatapi.sendToServer(message);
            message = input.nextLine();
        }
    }
}