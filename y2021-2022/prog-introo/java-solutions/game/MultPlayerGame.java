package game;

public class MultPlayerGame {
    private final Board board;
    private final Player[] players;
    private int count = 0;
    private int countPlayer;
    private final int[] lose;

    public MultPlayerGame(int m, int n, int k, Player[] players) {
        this.players = players;
        lose = new int[players.length];
        board = new TicTacToeBoard(m, n, k, players.length);
    }

    public int play(boolean log) {
        while (true) {
            if (lose[countPlayer] == 0) {
                try {
                    final int result = makeMove(players[countPlayer], countPlayer + 1, log);
                    if (result != -1) {
                        return result;
                    }
                } catch (NullPointerException e) {
                    System.out.println("Player " + (countPlayer + 1) +" take null");
                    lose[countPlayer] = 1;
                    board.changeTurn();
                    System.out.println(board);
                } catch (Exception e) {
                    System.out.println("Player " + (countPlayer + 1) +" throw exeption");
                    lose[countPlayer] = 1;
                    board.changeTurn();
                    System.out.println(board);
                }
            } else {
                board.changeTurn();
            }
            if (lose[countPlayer] == 1) {
                count++;
                lose[countPlayer] = 2;
            }
            countPlayer++;
            if (count == players.length - 1){
                return searchWinner() + 1;
            }
            if (countPlayer == players.length) {
                countPlayer = 0;
            }
        }
    }

    private int searchWinner() {
        for (int i = 0; i < 3; i ++) {
            if (lose[i] == 0) {
                return i;
            }
        }
        return 0;
    }

    private int makeMove(Player player, int no, boolean log) throws Exception{
        final Move move = player.makeMove(board.getPosition());
        final GameResult result = board.makeMove(move);
        if (log) {
            System.out.println();
            System.out.println("Player: " + no);
            System.out.println(move);
            System.out.println(board);
            if (result.equals(GameResult.LOSE)) {
                System.out.println("Player " + no + " lose");
            } else if (!result.equals(GameResult.WIN)) {
                System.out.println("Result " + result);
            }
        }
        switch (result) {
            case WIN:
                return no;
            case LOSE:
                lose[no - 1] = 1;
                return -1;
            case DRAW:
                return 0;
            case UNKNOWN:
                return -1;
            default:
                throw new AssertionError("Unknown makeMove result " + result);
        }
    }
}
