package game;

import java.util.Scanner;

public class HumanPlayer implements Player {
    private Scanner in;

    public HumanPlayer(Scanner in) {
        this.in = in;
    }

    @Override
    public Move makeMove(Position position) {
        Move move = null;
        while (true) {
            System.out.println();
            System.out.println("Current position");
            System.out.println(position);
            System.out.println("Enter you move for " + position.getTurn());
            try {
                move = new Move(in.nextInt() - 1, in.nextInt() - 1, position.getTurn());
                while (!position.isValid(move)) {
                    System.out.println("Sorry, but this cell has already full");
                    System.out.println();
                    System.out.println("Current position");
                    System.out.println(position);
                    System.out.println("Enter you move for " + position.getTurn());
                    move = new Move(in.nextInt() - 1, in.nextInt() - 1, position.getTurn());
                }
                break;
            } catch (NumberFormatException e) {
                System.out.println("Sorry, repite your enter");
                in = new Scanner(System.in);
            }
        }
        return move;
    }
}
