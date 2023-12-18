/*
1 2
3
*/

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class ReverseHex2 {

    static int[][] arrayTwoBigger(int[][] array) {
        array = Arrays.copyOf(array, array.length * 2);
        return array;
    }

    static int[] arrayOneBigger(int[] array, int num) {
        int b = array.length;
        array = Arrays.copyOf(array, array.length * 2);
        array[b] = num;
        return array;
    }

    public static void main(String[] args) {
    try {
        MyScaner scan = new MyScaner(System.in);
        int [][] bigArray = new int[10][];
        int j = -1;
        while (scan.hasNextLine()) {
            int[] arrayOne = new int[1];
            j++;
            int i = -1;
            while (scan.hasNextHexFast()) {
                int a = scan.nextHex();
                i++;
                arrayOne[0] = i;
                if (i >= arrayOne.length - 1) {
                    arrayOne = arrayOneBigger(arrayOne, a);
                } else {
                    arrayOne[i + 1] = a;
                }
                arrayOne[0]++;
            }
            while (j >= bigArray.length){
                bigArray = arrayTwoBigger(bigArray);
            }
            bigArray[j] = arrayOne;
        }

        for (int i = j; i >= 0; i--) {
            for (int k = bigArray[i][0]; k >= 0; k--) {
                if (k > 0) {
                    System.out.print(bigArray[i][k] + " ");
                }
            }
            System.out.println();
        }
            
    } catch (IOException e) {
        System.out.println(e.getMessage());
        }
    
    }
}