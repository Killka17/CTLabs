package game;

import java.util.Scanner;

public class SetMNK {

    static int m;
    static int n;
    static int k;


    public SetMNK() {
        while (true) {
            Scanner in = new Scanner(System.in);
            System.out.println("Введите m");
            if (in.hasNextLine()) {
                if (in.hasNextInt()) {
                    m = in.nextInt();
                } else {
                    continue;
                }
            } else {
                System.err.println("Закончен ввод");
                in.close();
                System.exit(0);
            }

            System.out.println("Введите n");
            if (in.hasNextLine()) {
                if (in.hasNextInt()) {
                    n = in.nextInt();
                } else {
                    continue;
                }
            }else {
                System.err.println("Закончен ввод");
                in.close();
                System.exit(0);
            }
            System.out.println("Введите k");
            if (in.hasNextLine()) {
                if (in.hasNextInt()) {
                    k = in.nextInt();
                } else {
                    continue;
                }
            }else {
                System.err.println("Закончен ввод");
                in.close();
                System.exit(0);
            }


            if (k <= 0 || m <= 0 || n <= 0) {

                System.err.println("Неверное значение таблицы");

            } else {
                break;
            }
        }

    }

    public static int getK() {
        return k;
    }

    public static int getM() {
        return m;
    }

    public static int getN() {
        return n;
    }
}
