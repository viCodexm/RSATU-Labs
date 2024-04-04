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
        System.out.print("Введите подстроку для поиска: ");
        String substring = scanner.nextLine();

        try (FileReader reader = new FileReader(inputFile);
             BufferedReader br = new BufferedReader(reader);
             FileWriter writer = new FileWriter(outputFile)) {

            List<LineCount> lineCounts = new ArrayList<>();
            String line;
            while ((line = br.readLine()) != null) {
                int count = (line.length() - line.replace(substring, "").length()) / substring.length();
                lineCounts.add(new LineCount(line, count));
            }

            lineCounts.sort(Comparator.comparing(LineCount::getCount).reversed());

            StringBuilder result = new StringBuilder();
            for (LineCount lc : lineCounts) {
                result.append(lc.getLine()).append(": ").append(lc.getCount()).append(System.lineSeparator());
            }

            writeStringBuilderContent(result, writer);
            System.out.println(result.toString());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void writeStringBuilderContent(StringBuilder content, FileWriter writer) throws IOException {
        writer.write(content.toString());
    }


    static class LineCount {
        private String line;
        private int count;

        public LineCount(String line, int count) {
            this.line = line;
            this.count = count;
        }

        public String getLine() {
            return line;
        }

        public int getCount() {
            return count;
        }
    }
}
