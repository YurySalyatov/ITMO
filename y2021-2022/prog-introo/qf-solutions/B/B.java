import java.util.Scanner;
public class B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        for (int i = -25_000; i <= 25_000; i++) {
            System.out.println(710 * i);
            n--;
            if (n == 0) {
                break;
            }
        }    
        sc.close();
    }
}
