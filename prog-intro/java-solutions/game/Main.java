package game;

import java.util.InputMismatchException;
import java.util.Map;
import java.util.Scanner;

/**
 * @author Georgiy Korneev / Ivan Gusarov (kgeorgiy@kgeorgiy.info)
 */
public class Main {
    private static final Map<Integer, String> RES = Map.of(
            1, "X WIN",
            2, "O WIN",
            0, "DRAW"
    );

    public static void main(String[] args) {

        System.out.println("Если хотите сыграть турнир - введите 1, если в mnk - введите любое другое число ");
        int a = -1;
        Scanner sc;
        while (true) {
            sc = new Scanner(System.in);
            if (sc.hasNextLine()) {
                if (sc.hasNextInt()) {
                    a = sc.nextInt();
                    break;
                } else {
                    System.err.println("Введено неверное значение");
                }
            } else {
                System.err.println("Закончен ввод");
                sc.close();
                System.exit(0);
            }
        }
        if (a == 1) {
            System.out.println("Введите количество игроков ");
            if (sc.hasNextLine()) {
                if (sc.hasNextInt()) {
                    int count = sc.nextInt();
                    if (count > 0) {
                        Raspred raspred = new Raspred(count);
                    } else {
                        System.err.println("Введено неверное количество игроков");
                        sc.close();
                        System.exit(0);
                    }
                } else {
                    System.err.println("Количесиво игроков не введено");
                    sc.close();
                    System.exit(0);
                }
            } else {
                System.err.println("Ввод завершён");
                sc.close();
                System.exit(0);
            }

        } else {
            final Game game = new Game(false, new HumanPlayer(), new HumanPlayer());
            int result;
            do {
                SetMNK setMNK = new SetMNK();
                result = game.play(new Mnk());
                System.out.println("Game result: " + RES.get(result));
            } while (result != 0);
        }
    }
}

