import java.nio.charset.StandardCharsets;
import java.util.*;
import java.io.*;

public class Wspp {
    public static void main(String[] args) {
        Map <String, MyIntList> mapInt = new LinkedHashMap<>();
        String fileIn = args[0];
        String fileOut = args[1];
//         String fileIn = "test1in.txt";
  //       String fileOut = "test1out.txt";
        try {
            MyScaner sc = new MyScaner(fileIn, "utf8");
            int countWord = 0;
            while (sc.hasNextLine()) {
                String line = sc.nextLine().toLowerCase();
                MyScaner scanLine = new MyScaner(line);
                try{
                    while (scanLine.hasNextWord()) {
                        String word = scanLine.nextWord();
                        countWord++;
                        if (mapInt.containsKey(word)) {
                            MyIntList ar = mapInt.get(word);
                            ar.add(countWord);
                            mapInt.put(word, ar);
                        } else {
                            MyIntList ar = new MyIntList();
                            ar.add(countWord);
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
                    out.write(it + " " + mapInt.get(it).toString(""));
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
