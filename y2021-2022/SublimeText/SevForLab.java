import java.util.Scanner;

public class SevForLab {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		int[] answer = new int[t];
		for (int i = 0; i < t; i++) {
			int a = in.nextInt();
			if (a % 2 == 0) {
				answer[i] = a / 2;
			} else {
				answer[i] = (a - 1) / 2 + 1;
			}
		}
		for (int i = 0; i < t; i++) {
			System.out.println(answer[i]);
		}
		in.close();
	}
}