import java.util.Scanner;

public class SiForLab {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int t = in.nextInt();
		int[] qwiz = new int[t];
		for (int i = 0; i < t; i++) {
			qwiz[i] = in.nextInt();
		}
		int first = 0;
		int last = t - 1;
		int countSerg = 0;
		int countDim = 0;
		for (int i = 0; i < t; i++) {
			if (i % 2 == 0) {
				if (qwiz[first] > qwiz[last]) {
					countSerg += qwiz[first];
					first++;
				} else {
					countSerg += qwiz[last];
					last--;
				}
			} else {
				if (qwiz[first] > qwiz[last]) {
					countDim += qwiz[first];
					first++;
				} else {
					countDim += qwiz[last];
					last--;
				}
			}
		}
		System.out.print(countSerg);
		System.out.print(" ");
		System.out.println(countDim);
		in.close();
	}
}