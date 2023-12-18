package game;

public class ExeptionPlayer implements Player{

    @Override
    public Move makeMove(Position position) throws Exception {
        throw new Exception();
    }
    
}
