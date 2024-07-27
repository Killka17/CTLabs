import java.util.*;

public class m {

    public static void main(String[] args) {

        Scanner scn = new Scanner(System.in);

        int t = scn.nextInt();


        for (int m = 0; m < t; m++) {

            int n = scn.nextInt();
            int[] a = new int[n];
            for (int p = 0; p < n; p++) {
                a[p] = scn.nextInt();

            }



            int counter = 0;
            HashMap <Integer, Integer> c = new HashMap<>();


            for (int j = n - 1; j > 0; j--) {

                for (int i = 0; i < j; i++) {

                    if (c.get(2 * a[j] - a[i]) != null) {
                        counter += c.get(2 * a[j] - a[i]);
                    }
                }

                    if (c.get(a[j]) != null) {

                        c.put(a[j], c.get(a[j]) + 1);
                    } else {
                        c.put(a[j], 1);
                    }

            }


            c.clear();
            System.out.println(counter);
        }

    }

}
