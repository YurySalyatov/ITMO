package game;

import java.util.Arrays;
import java.util.Map;

public class TicTacToeBoard implements Board, Position {
    private static final Map<Cell, String> CELL_TO_STRING = Map.of(
            Cell.E, ".",
            Cell.X, "X",
            Cell.O, "0",
            Cell.T, "-",
            Cell.F, "|");

    private final Cell[][] field;
    private Cell turn;
    private int rows;
    private int cols;
    private int winCount;
    private int playerCount;
    private Cell[] cellAray = new Cell[] { Cell.X, Cell.O, Cell.T, Cell.F };
    private int turnCount = 0;

    public TicTacToeBoard(int rows, int cols, int winCount, int playerCount) {
        this.rows = rows;
        this.cols = cols;
        this.winCount = winCount;
        this.playerCount = playerCount;
        field = new Cell[rows][cols];
        for (Cell[] row : field) {
            Arrays.fill(row, Cell.E);
        }
        turn = cellAray[turnCount];
    }

    @Override
    public Cell getTurn() {
        return turn;
    }

    @Override
    public Position getPosition() {
        return this;
    }

    public int getRows() {
        return rows;
    }

    public int getCol() {
        return cols;
    }

    @Override
    public GameResult makeMove(Move move) {
        if (!isValid(move)) {
            changeTurn();
            return GameResult.LOSE;
        }
        field[move.getRow()][move.getCol()] = move.getCell();
        if (checkWin()) {
            return GameResult.WIN;
        }
        
        if (checkDraw()) {
            return GameResult.DRAW;
        }
        changeTurn();
        return GameResult.UNKNOWN;
    }

    public void changeTurn() {
        turnCount++;
        if (turnCount == playerCount) {
            turnCount = 0;
        }
        turn = cellAray[turnCount];
    }

    private boolean checkDraw() {
        int count = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (field[r][c] == Cell.E) {
                    count++;
                }
            }
        }
        if (count == 0) {
            return true;
        }
        return false;
    }

    private boolean checkWin() {
        for (int r = 0; r < rows; r++) {
            int count = 0;
            for (int c = 0; c < cols; c++) {
                if (field[r][c] == turn) {
                    count++;
                    if (count == winCount) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
        }
        for (int c = 0; c < cols; c++) {
            int count = 0;
            for (int r = 0; r < rows; r++) {
                if (field[r][c] == turn) {
                    count++;
                    if (count == winCount) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
        }

        for (int c = 0; c < cols; c++) {
            int count = 0;
            for (int r = 0; r < Math.min(rows, cols - c); r++) {
                if (field[r][c + r] == turn) {
                    count++;
                    if (count == winCount) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
        }
        for (int r = 0; r < rows; r++) {
            int count = 0;
            for (int c = 0; c < Math.min(rows - r, cols); c++) {
                if (field[r + c][c] == turn) {
                    count++;
                    if (count == winCount) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
        }

        for (int c = cols - 1; c >= 0; c--) {
            int count = 0;
            for (int r = 0; r < Math.min(rows, c); r++) {
                if (field[r][c - r] == turn) {
                    count++;
                    if (count == winCount) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
        }
        for (int r = 0; r < rows; r++) {
            int count = 0;
            for (int c = 0; c < Math.min(rows - r, cols); c++) {
                if (field[r + c][cols - 1 - c] == turn) {
                    count++;
                    if (count == winCount) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
        }

        return false;
    }

    public boolean isValid(final Move move) {
        return move.getCell() != null 
                && 0 <= move.getRow() && move.getRow() < rows
                && 0 <= move.getCol() && move.getCol() < cols
                && field[move.getRow()][move.getCol()] == Cell.E
                && turn == move.getCell();
    }

    @Override
    public Cell getCell(int row, int column) {
        return field[row][column];
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("");
        String strCols = Integer.toString(cols);
        String strRows = Integer.toString(rows);
        for (int i = 0; i < strRows.length(); i++) {
            sb.append(" ");
        }
        for (int c = 0; c < cols; c++) {
            String strNow = Integer.toString(c + 1);
            for (int i = 0; i < strCols.length() - strNow.length() + 1; i++) {
                sb.append(" ");
            }
            sb.append(c + 1);
        }
        sb.append(System.lineSeparator());
        sb.append(System.lineSeparator());
        for (int r = 0; r < rows; r++) {
            for (int i = 0; i < strRows.length() - Integer.toString(r + 1).length(); i++) {
                sb.append(" ");
            }
            sb.append(r + 1);
            for (Cell cell : field[r]) {
                for (int j = 0; j < strCols.length(); j++) {
                    sb.append(" ");
                }
                sb.append(CELL_TO_STRING.get(cell));
            }
            sb.append(System.lineSeparator());
            sb.append(System.lineSeparator());
        }
        sb.setLength(sb.length() - System.lineSeparator().length());
        return sb.toString();
    }
}
