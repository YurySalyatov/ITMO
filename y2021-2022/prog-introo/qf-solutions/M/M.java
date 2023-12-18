import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;

public class M {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int allCount = sc.nextInt();
        for (int count = 0; count < allCount; count++) {
            int countI = sc.nextInt();
            long res = 0;
            int[] a = new int[countI];
            for (int i = 0; i < countI; i++) {
                a[i] = sc.nextInt();
            }
            Map<Integer, Integer> hashMap = new HashMap<Integer, Integer>();
            for (int j = countI - 1; j >= 0; j--) {
                for (int i = 0; i < j; i++) {
                    res += hashMap.getOrDefault(2 * a[j] - a[i],0);
                }
                if (hashMap.containsKey(a[j])) {
                    hashMap.put(a[j], hashMap.get(a[j]) + 1);
                } else {
                    hashMap.put(a[j], 1);
                }
            }
            System.out.println(res);
        }
        sc.close();
    }
}
