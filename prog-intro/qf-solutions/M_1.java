import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class m {

    public static void main(String[] args) {

        Scanner scn = new Scanner(System.in);

        int t = scn.nextInt();


        for (int m = 0; m < t; m++) {

            int n = scn.nextInt();
            int[] a = new int[n];
            for (int p = 0; p < n; p++) {
                a[p] = (scn.nextInt());
            }
            System.out.println(Arrays.toString(a));


            int counter = 0;

            for (int j = n - 1; j > 0; j--) {

                for (int i = 0; i < j; i++) {

                    for (int k = j + 1; k < n; k++) {

                        if (a[k] == 2 * a[j] - a[i]) {

                            counter++;
                        }

                    }

                }

            }

            System.out.println(counter);
            if (scn.nextLine() == "\n") {
                break;
            }

        }

    }

}
