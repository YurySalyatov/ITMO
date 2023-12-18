package game;

public class SequentialPlayer implements Player {
    private int r = 0;
    private int c = 0;
    @Override
    public Move makeMove(Position position) {
        while(r < position.getRows()) {
            while (c < position.getCol()) {
                final Move move = new Move(r, c, position.getTurn());
                c++;
                return move;
            }
            r++;
        }
        throw new AssertionError("No valid moves");
    }
}
