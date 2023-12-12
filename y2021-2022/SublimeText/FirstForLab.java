import java.util.Scanner;

public class FirstForLab {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		int[] answer = new int[t];
		for (int i = 0; i < t; i++) {
			int a = in.nextInt();
			int b = in.nextInt();
			int h = Math.max(a, b);
			int w =  2 * Math.min(a, b);
			int sq = Math.max(h, w);
			answer[i] = sq * sq;
		}
		for (int i = 0; i < t; i++) {
			System.out.println(answer[i]);
		}
	}
}