import java.util.Scanner;

public class NForLab {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String qwiz = in.nextLine();
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < qwiz.length(); i++) {
			if (qwiz.charAt(i) == '.') {
				sb.append("0");
			} else {
				i++;
				if (qwiz.charAt(i) == '.') {
					sb.append("1");
				} else {
					sb.append("2");
				}
			}
		}
		System.out.println(sb.toString());
	}
}