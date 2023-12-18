import java.nio.charset.StandardCharsets;
import java.util.*;
import java.io.*;

public class WordStatInput {
    public static void main(String[] args) {
        Map <String, Integer> mapInt = new LinkedHashMap<>();
        String fileIn = args[0];
        String fileOut = args[1];
        // String fileIn = "test1in.txt";
        // String fileOut = "test1out.txt";
        try {
            MyScaner sc = new MyScaner(fileIn, "utf8");
            while (sc.hasNextLine()) {
                String line = sc.nextLine().toLowerCase();
                MyScaner scanLine = new MyScaner(line);
                try{
                    while (scanLine.hasNextWord()) {
                        String word = scanLine.nextWord();
                        if (mapInt.containsKey(word)) {
                            int ar = mapInt.get(word);
                            ar++;
                            mapInt.put(word, ar);
                        } else {
                            int ar = 1;
                            mapInt.put(word, ar);
                        }
                    }
                } catch (IOException e) {
                    System.out.println("Something wrog in file: " + e.getMessage());
                } finally {
                    scanLine.close();
                }
            }
            BufferedWriter out = new BufferedWriter(
                new OutputStreamWriter(
                    new FileOutputStream(fileOut),
                        StandardCharsets.UTF_8
                )
            );
            try {
                for (String it: mapInt.keySet()) {
                    out.write(it + " " + mapInt.get(it));
                    out.newLine();
                }
            } finally {
                sc.close();
                out.close();
            }
        } catch (IOException e) {
            System.out.println("Something wrog with file: " + e.getMessage());
        }
    }
}
