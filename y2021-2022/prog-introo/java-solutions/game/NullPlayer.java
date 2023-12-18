package game;

public class NullPlayer implements Player{

    @Override
    public Move makeMove(Position position) {
        return null;
    }
    
}
