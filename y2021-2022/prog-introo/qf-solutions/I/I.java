import java.util.Scanner;
public class I {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int xl = 100_000_001;
        int xr = -100_000_001;
        int yl = 100_000_001;
        int yr = -100_000_001;
        for (int i = 0; i < n; i++) {
                int xi = sc.nextInt();
                int yi = sc.nextInt();
                int hi = sc.nextInt();
                xl = Math.min(xi - hi, xl);
                xr = Math.max(xi + hi, xr);
                yl = Math.min(yi - hi, yl);
                yr = Math.max(yi + hi, yr);
        }
        System.out.print((xl + xr) / 2 + " ");
        System.out.print((yl + yr) / 2 + " ");
        System.out.println((int) Math.ceil(((double)Math.max(xr - xl, yr - yl)) / 2));
        sc.close();
    }
}
