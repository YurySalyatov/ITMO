import java.util.Scanner;
public class A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int b = sc.nextInt();
        int n = sc.nextInt();
        if ((n - b) % (b - a) == 0) {
            System.out.println(2*((n - b)/(b-a)) + 1);
        } else {
            System.out.println(2*((n - b)/(b-a) + 1) + 1);
        }
        sc.close();
    }
} 