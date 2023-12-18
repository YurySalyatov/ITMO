
import java.io.*;

public class Sum {
    public static boolean symbolIsADigit (char symbol) {
        return (symbol >= '0' && symbol <= '9');
    }
    public static void main (String args[]) {
        int sum = 0;
        for (int i =0; i < args.length; i++) {
            int a = 0;
            int add = 1;
            for (int j = 0; j < args[i].length(); j++) {
                char symbol = args[i].charAt(j);
                if (symbol == '-') {
                    add = -1;
                }
                if (symbolIsADigit(symbol)) {
                    a *= 10;
                    a += (symbol - '0');
                }
                else {
                    sum += (a*add);
                    a = 0;
                    if (symbol != '-') {
                        add = 1; 
                    }
                }
                if (j == args[i].length() - 1){
                    sum += (a*add);
                    add = 1;
                }
            }
        }
        System.out.println(sum);
    }
}
