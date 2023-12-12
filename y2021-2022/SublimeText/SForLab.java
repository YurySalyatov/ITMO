import java.util.Scanner;

public class SForLab {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		in.nextLine();
		String[] answer = new String[t];
		for (int i = 0; i < t; i++) {
			String qwiz = in.nextLine();
			answer[i] = qwiz;
		}
		for (int i = 0; i < t; i++) {
			if (answer[i].length() > 10) {
				System.out.print(answer[i].charAt(0));
				System.out.print((answer[i].length() - 2));
				System.out.println(answer[i].charAt(answer[i].length() - 1));
			} else {
				System.out.println(answer[i]);
			}
		}
	}
}