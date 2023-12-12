import java.util.Scanner;

public class FoForLab {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		int[] answer = new int[t];
		for (int i = 0; i < t; i++) {
			int x = in.nextInt();
			int y = in.nextInt();
			int n = in.nextInt();
			if (n % x > y) {
				answer[i] = n - (n % x) + y;
			} else {
				if (n % x == y) {
					answer[i] = n;
				} else {
					answer[i] = n - (n % x) + y - x ; 
				}
			}
		}
		for (int i = 0; i < t; i++) {
			System.out.println(answer[i]);
		}
		in.close();
	}
}