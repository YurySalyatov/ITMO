package game;

import java.util.Random;

public class RandomPlayer implements Player {
    private final Random random = new Random();

    @Override
    public Move makeMove(Position position) {
        final Move move = new Move(
                random.nextInt(position.getRows()),
                random.nextInt(position.getCol()),
                position.getTurn());
                return move;
    }
}
