/**
 * SumFloat
 */
public class SumFloat {
    public static void main(String[] args) {
        float sum = 0;
        for (int i = 0; i < args.length; i++) {
            int begin = 0;
            for (int j = 0; j < args[i].length(); j++) {
                char symbol = args[i].charAt(j);
                if (Character.isWhitespace(symbol)) {
                    if (j - begin > 0) {
                        sum += Float.parseFloat(args[i].substring(begin,j));
                    }
                    begin = j + 1;
                }
                if (j == args[i].length() - 1 && !Character.isWhitespace(symbol)) {
                    sum += Float.parseFloat(args[i].substring(begin));
                }
            }
        }
        System.out.println(sum);
    }
}