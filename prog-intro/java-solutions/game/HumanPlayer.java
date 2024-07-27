package game;

import java.io.PrintStream;
import java.util.Scanner;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class HumanPlayer extends AbstractPlayer {
    private final PrintStream out;
    private final Scanner in;


    public HumanPlayer(final PrintStream out, final Scanner in) {
        this.out = out;
        this.in = in;
    }

    public HumanPlayer() {
        this(System.out, new Scanner(System.in));
    }

    @Override
    public Move move(final Position position, final Cell cell) {
        while (true) {
            out.println("Position");
            out.println(position);
            out.println(cell + "'s move");
            final Move move;
            int firstCell = 0;
            int secondCell = 0;
            while (true) {
                Scanner in = new Scanner(System.in);
                out.println("Enter row and column");

                if (in.hasNextLine()) {
                    if (in.hasNextInt()) {
                        firstCell = in.nextInt();
                    } else {
                        System.err.println("Неверное значение");
                        continue;
                    }
                } else {
                    System.err.println("Закончен ввод");
                    in.close();
                    System.exit(0);
                }
                if (in.hasNextLine()) {
                    if (in.hasNextInt()) {
                        secondCell = in.nextInt();
                        break;
                    } else {
                        System.err.println("Неверное значение");
                    }
                } else {
                    System.err.println("Закончен ввод");
                    in.close();
                    System.exit(0);
                }
            }
            move = new Move(firstCell, secondCell, cell);
            if (position.isValid(move)) {
                return move;
            }
            out.println("Move " + move + " is invalid");
        }
    }
}
