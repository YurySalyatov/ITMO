import java.util.*;
import java.io.*;

public class WordStatCount {
    static int[] changeArrayInt (int [] counters) {
        counters = Arrays.copyOf(counters, counters.length + 1);
        counters[counters.length - 1] = 1;
        return (counters);
    }
    static int[] changeArrays (String word, ArrayList<String> words, int[] counters) {
        int newsWord = 0;
        for (int j = 0; j < words.size(); j++) {
            if (word.equals(words.get(j))) {
                counters[j] = counters[j] + 1;
                break;
            }
            newsWord++;
        }
        if (newsWord == words.size()) {
            words.add(word);
            counters = changeArrayInt(counters);
        }
        return (counters);
    }
    public static void main(String[] args) {
        String fileIn = args[0];
        String fileOut = args[1];
        // String fileIn = "input.txt";
        // String fileOut = "output.txt";
        int max = 1;
        try {
            BufferedReader in = new BufferedReader(
                new InputStreamReader(
                    new FileInputStream(fileIn),
                "utf8"
                )
            );
            StringBuilder sb = new StringBuilder();
            try {
                while (true) {
                    String line = in.readLine();
                    if (line == null) {
                        break;
                    }
                    sb.append(line.toLowerCase() + ' ');
                }
            } finally{
                in.close();
            }
            ArrayList<String> words = new ArrayList<>();
            int[] counters = new int[0];
            int begin = 0;
            for (int i = 0; i < sb.length(); i++) {
                char symbol = sb.charAt(i);
                if (!Character.isLetter(symbol) && symbol != '\'' && Character.getType(symbol) != Character.DASH_PUNCTUATION) {
                    if (i - begin > 0) {
                        String word = sb.substring(begin, i);
                        counters = changeArrays(word, words, counters);
                    }
                    begin = i + 1;
                }
                if (i == sb.length() - 1 && (Character.isLetter(symbol) || symbol == '\'' || Character.getType(symbol) == Character.DASH_PUNCTUATION)) {
                    String word = sb.substring(begin);
                    counters = changeArrays(word, words, counters);
                }
            }
            for (int i = 0; i < counters.length; i++) {
                if (max < counters[i]) {
                    max = counters[i];
                }
            }
            BufferedWriter out = new BufferedWriter(
                new OutputStreamWriter(
                    new FileOutputStream(fileOut),
                "utf8"
                )
            );
            try {
                for (int j = 1; j <= max; j++) {
                    for (int i = 0; i < words.size(); i++) {
                        if (counters[i] == j) {
                            out.write(words.get(i) + " " + counters[i]);
                            out.newLine();
                        }
                    }
                }
            } finally {
                out.close();
            }
       } catch (IOException e) {
           System.out.println("cannot read or write file: " + e.getMessage());
       }  
    }
}