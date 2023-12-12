import java.util.Scanner;

public class TeForLab {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		int[] answer = new int[t];
		for (int i = 0; i < t; i++) {
			int h = in.nextInt();
			int m = in.nextInt();
			answer[i] = (23 - h) * 60 + (60 - m);
		}
		for (int i = 0; i < t; i++) {
			System.out.println(answer[i]);
		}
		in.close();
	}
}