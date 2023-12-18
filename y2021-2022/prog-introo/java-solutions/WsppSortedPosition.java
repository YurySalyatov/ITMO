import java.nio.charset.StandardCharsets;
import java.util.*;
import java.io.*;

public class WsppSortedPosition {
    public static void main(String[] args) {
        Map <String, MyIntList> mapInt = new TreeMap<>();
        String fileIn = args[0];
        String fileOut = args[1];
        // String fileIn = "test1in.txt";
        // String fileOut = "test1out.txt";
        try {
            MyScaner sc = new MyScaner(fileIn, "utf8");
            int countStr = 0;
            int countWord = 0;
            while (sc.hasNextLine()) {
                countStr++;
                String line = sc.nextLine().toLowerCase();
                MyScaner scanLine = new MyScaner(line);
                while (scanLine.hasNextWord()) {
                    String word = scanLine.nextWord();
                    countWord++;
                    if (mapInt.containsKey(word)) {
                        MyIntList listAr = mapInt.get(word);
                        listAr.add(countStr, countWord);
                        mapInt.put(word, listAr);
                    } else {
                        MyIntList listAr = new MyIntList();
                        listAr.add(countStr, countWord);
                        mapInt.put(word, listAr);
                    }
                }
                countWord = 0;
            }
            BufferedWriter out = new BufferedWriter(
                new OutputStreamWriter(
                    new FileOutputStream(fileOut),
                "utf8"
                )
            );
            try {
                for (String it: mapInt.keySet()) {
                    out.write(it + " " + mapInt.get(it).toString(0));
                    out.newLine();
                }
            } finally {
                sc.close();
                out.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
