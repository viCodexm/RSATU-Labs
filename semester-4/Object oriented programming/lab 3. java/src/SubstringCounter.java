import java.io.*;
import java.util.*;

public class SubstringCounter {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java SubstringCounter <inputFile> <outputFile>");
            return;
        }

        String inputFile = args[0];
        String outputFile = args[1];
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the substring to search for:");
        String substring = scanner.nextLine();

        try (FileReader reader = new FileReader(inputFile);
             BufferedReader br = new BufferedReader(reader)) {
            String line;
            PriorityQueue<String> queue = new PriorityQueue<>(Comparator.comparingInt(s -> -s.split(substring, -1).length + 1));
            while ((line = br.readLine()) != null) {
                queue.add(line);
            }

            try (FileWriter writer = new FileWriter(outputFile)) {
                while (!queue.isEmpty()) {
                    writer.write(queue.poll() + System.lineSeparator());
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
