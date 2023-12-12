import java.util.Scanner;

public class FiForLab {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		in.nextLine();
		int full = 10;
		int[] answer = new int[t];
		for (int i = 0; i < t; i++) {
			String qwiz = in.nextLine();
			int count = Integer.parseInt(qwiz.substring(0,1)) - 1;
			int last = 0;
			for (int j = 0; j < qwiz.length(); j++) {
				last += j + 1;
			}
			answer[i] = count * full + last;
		}
		for (int i = 0; i < t; i++) {
			System.out.println(answer[i]);
		}
		in.close();
	}
}