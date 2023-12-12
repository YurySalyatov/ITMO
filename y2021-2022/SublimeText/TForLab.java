import java.util.Scanner;

public class TForLab {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		int[] answer = new int[t];
		for (int i = 0; i < t; i++) {
			int n = in.nextInt();
			int a = in.nextInt();
			int b = in.nextInt();
			boolean yes = true;
			if (a == b) {
				for (int j = 2; j < n; j++) {
					int c = in.nextInt();
					if (c != a && yes) {
						answer[i] = j + 1;
						yes = false;
					}
				}
			} else {
				for (int j = 2; j < n; j ++) {
					int c = in.nextInt();
					if (c != a && yes) {
						yes = false;
						answer[i] = 1;
					}
					if (c != b && yes) {
						yes = false;
						answer[i] = 2;
					}
				}
			}
		}
		for (int i = 0; i < t; i++) {
			System.out.println(answer[i]);
		} 
	}
}