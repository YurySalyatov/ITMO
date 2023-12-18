package game;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("Please, give rows, cols, wincost and number of player");
        Scanner sc = new Scanner(System.in);
        int m = sc.nextInt();
        int n = sc.nextInt();
        int k = sc.nextInt();
        int playerCount = sc.nextInt();
        Player[] players = new Player[playerCount];
        while (true) {
            System.out.println("You can chouse players:" + System.lineSeparator() + "R - random player, " + "H - human player "
                    + "S - sequential player," + System.lineSeparator() + "N - null player, " + "E - exeption player");
            int count = 0;
            for (int i = 0; i < playerCount; i++) {
                String str = sc.next();
                if (str.equals("R")) {
                    players[i] = new RandomPlayer();
                    count++;
                } else if (str.equals("H")) {
                    players[i] = new HumanPlayer(sc);
                    count++;
                } else if (str.equals("S")) {
                    players[i] = new SequentialPlayer();
                    count++;
                } else if (str.equals("N")) {
                    players[i] = new NullPlayer();
                    count++;
                } else if (str.equals("E")) {
                    players[i] = new ExeptionPlayer();
                    count++;
                }
            }
            if (count == playerCount) {
                break;
            } else {
                System.out.println("Retry, please");
            }
        }
        final int result = new MultPlayerGame(m, n, k, players).play(true);
        switch (result) {
            case 1:
                System.out.println("First player won");
                break;
            case 2:
                System.out.println("Second player won");
                break;
            case 3:
                System.out.println("Theard player won");
                break;
            case 4:
                System.out.println("Fourth player won");
                break;
            case 0:
                System.out.println("Draw");
                break;
            default:
                throw new AssertionError("Unknow makeMove " + result);
        }
    }
}
