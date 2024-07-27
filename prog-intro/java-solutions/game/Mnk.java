package game;

import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Map;
import java.util.Scanner;

/**
 * @author Ivan Gusarov, Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Mnk implements Board, Position {
    private static final Map<Cell, Character> SYMBOLS = Map.of(
            Cell.X, 'X',
            Cell.O, 'O',
            Cell.E, '.'
    );
    private final Cell[][] cells;
    private Cell turn;


    int subsequence = 0;
    int lastSubsequenceX = 0;
    int lastSubsequenceY = 0;
    int f = 0;

    final int m = SetMNK.getM();
    final int n = SetMNK.getN();
    final int k = SetMNK.getK();

    public Mnk() {
        this.cells = new Cell[m][n];
        for (Cell[] row : cells) {
            Arrays.fill(row, Cell.E);
        }
        turn = Cell.X;
    }

    @Override
    public Position getPosition() {
        return this;
    }

    @Override
    public Cell getCell() {
        return turn;
    }

    @Override
    public Result makeMove(final Move move) {

        if (!isValid(move)) {
            if (f % 2 == 0) {
                return Result.LOSE;
            } else {
                return Result.WIN;
            }
        }

        cells[move.row()][move.column()] = move.value();


        int empty = 0;
        for (int u = 0; u < m; u++) {
            int inRow = 0;
            int inColomn = 0;
            for (int v = 0; v < n; v++) {
                if (cells[u][v] == turn) {
                    inRow++;
                    inColomn++;
                    for (int t = 1; t < k; t++) {
                        if (isValidCell(u, v + t) && cells[u][v + t] == turn) {
                            inRow++;
                            if (inRow == k) {
                                if (f % 2 == 0) {
                                    return Result.WIN;
                                } else {
                                    return Result.LOSE;
                                }
                            }
                        } else {
                            if (inRow >=4) {
                                subsequence++;
                            }
                            inRow = 0;
                            break;
                        }
                    }

                    for (int p = 1; p < k; p++) {
                        if (isValidCell(u + p, v) && cells[u + p][v] == turn) {
                            inColomn++;
                            if (inColomn == k) {
                                if (f % 2 == 0) {
                                    return Result.WIN;
                                } else {
                                    return Result.LOSE;
                                }
                            }
                        } else {
                            if (inColomn >= 4) {
                                subsequence++;
                            }
                            inColomn = 0;
                            break;
                        }
                    }
                }
                if (cells[u][v] == Cell.E) {
                    empty++;
                }
            }
        }

        int counter1 = 0;
        int counter2 = 0;


        for (int u = 0; u < m; u++) {
            for (int v = 0; v < n; v++) {
                if (cells[u][v] == turn) {
                    counter1++;
                    counter2++;
                    for (int z = 1; z < k + 1; z++) {
                        if (isValidCell(u + z, v - z) && cells[u + z][v - z] == turn) {
                            counter1++;
                        } else {
                            break;
                        }
                    }
                    for (int z = 1; z < k + 1; z++) {

                        if (isValidCell(u - z, v - z) && cells[u - z][v - z] == turn) {
                            counter2++;
                        } else {
                            break;
                        }
                    }

                    if (counter1 >= k || counter2 >= k) {
                        if (f % 2 == 0) {
                            return Result.WIN;
                        } else {
                            return Result.LOSE;
                        }

                    } else if (counter1 >= 4 || counter2 >= 4) {
                        subsequence++;
                    }
                }
                    counter1 = 0;
                    counter2 = 0;
                }
            }

        if (empty == 0) {
            return Result.DRAW;
        }

        int x = move.row();
        int y = move.column();

        if (lastSubsequenceX < subsequence && getCell() == Cell.X) {
            f++;
            lastSubsequenceX = subsequence;
        } else if (lastSubsequenceY < subsequence && getCell() == Cell.O) {
            f++;
            lastSubsequenceY = subsequence;
        } else {
            turn = turn == Cell.X ? Cell.O : Cell.X;
        }
        subsequence = 0;

        return Result.UNKNOWN;
    }
    @Override
    public boolean isValid(final Move move) {

        return 0 <= move.row() && move.row() < m
                && 0 <= move.column() && move.column() < n
                && cells[move.row()][move.column()] == Cell.E
                && turn == getCell();
    }
    public boolean isValidCell(int x, int y) {return x < m && y < n && x >= 0 && y >= 0;}
    @Override
    public Cell getCell(final int r, final int c) {
        return cells[r][c];
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder(" ");
        for (int k = 0; k < n; k++) {
            sb.append(k);
        }
        for (int r = 0; r < m; r++) {
            sb.append("\n");
            sb.append(r);
            for (int c = 0; c < n; c++) {
                sb.append(SYMBOLS.get(cells[r][c]));
            }
        }
        return sb.toString();
    }
}
