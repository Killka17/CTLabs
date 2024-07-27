import java.util.Arrays;
import java.util.Scanner;

public class laba {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();

        int[][] list = new int[n][n];

        for (int i = 0; i < n; i++) {

            String str = scanner.next();


            for (int j = 0; j < n; j++) {

                list[i][j] = Integer.parseInt(str.charAt(j) + "");

            }
        }


        for (int k = 0; k < n; k++) {

            for (int i = 0; i < n; i++) {

                if (list[k][i] != 0 && k < i) {

                    for (int j = 0; j < n; j++) {

                        if (j > i) {
                            list[k][j] = list[k][j] - list[i][j];
                        }




                    }

                }

            }

        }


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (list[i][j] == 0) {

                    System.out.print(0);

                } else {
                    System.out.print(1);
                }

            }
            System.out.println();
        }



    }
}
