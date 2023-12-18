

import java.io.IOException;
import java.util.*;

public class ReverseTranspose {
    static int[][] arrayTwoBegger (int[][] array) {
        array = Arrays.copyOf(array, array.length * 2);
        return array;
    }
    static int[] arrayOneBegger (int[] array, int num) {
        array = Arrays.copyOf(array, array.length + 1);
        array[array.length - 1] = num;
        return array;
    }
    public static void main(String[] args) {
        try {
            MyScaner scan = new MyScaner(System.in);
            int[][] array = new int[10][];
            int j = -1;
            int maxx = 0;
            while (scan.hasNextLine()) {
                int[] list = new int[0];
                while (scan.hasNextIntFast()) {
                    list = arrayOneBegger(list, scan.nextInt());
                }
                    j++;
                    while (j >= array.length) {
                        array = arrayTwoBegger(array);
                    }
                    array[j] = list;
                    if (maxx < list.length) {
                        maxx = list.length;
                    }
            }
            for (int i = 0; i < maxx; i++) {
                for (int k = 0; k <= j; k++) {
                    if (i < array[k].length) {
                        System.out.print(array[k][i] + " ");
                    }
                }
                System.out.println();
            }
            scan.close();
        } catch (IOException e) {
            System.out.println("Something wrong with input: " + e.getMessage());
        }
    }
}