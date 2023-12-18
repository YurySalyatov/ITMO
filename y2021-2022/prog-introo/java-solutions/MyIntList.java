
import java.util.Arrays;

public class MyIntList {

    public int lenghtList;
    public int[] intAr;
    public MyIntList() {
        this.intAr = new int[]{0};
        this.lenghtList = intAr[0];
    }
    public void add (int number) {
        while (intAr.length - 1 <= this.lenghtList) {
            this.intAr = Arrays.copyOf(this.intAr, intAr.length * 2);
        }
        this.intAr[this.lenghtList + 1] = number;
        this.intAr[0]++;
        this.lenghtList++;
    }
    public void add (int numberStr, int numberWord) {
        while (intAr.length - 2 <= 2 * this.lenghtList) {
            this.intAr = Arrays.copyOf(this.intAr, intAr.length * 2);
        }
        this.intAr[2 * this.lenghtList + 1] = numberStr;
        this.intAr[2 * this.lenghtList + 2] = numberWord;
        this.intAr[0]++;
        this.lenghtList = intAr[0];
    }
    public String toString (int val) {
        StringBuilder sb = new StringBuilder();
        sb.append(this.intAr[0]);
        for (int i = 1; i <= 2 * this.lenghtList; i++) {
            i++;
            if (i != 2 * this.lenghtList - 1) {
                sb.append(" ");
            }
            sb.append(this.intAr[i - 1] + ":" + this.intAr[i]);
        }
        return sb.toString();
    }
    public String toString (String val) {
        StringBuilder sb = new StringBuilder();
        sb.append(this.intAr[0]);
        for (int i = 1; i <= this.lenghtList; i++) {
            sb.append(" ");
            sb.append(this.intAr[i]);
        }
        return sb.toString();
    }
    public int getLenght() {
        return this.lenghtList;
    }
}