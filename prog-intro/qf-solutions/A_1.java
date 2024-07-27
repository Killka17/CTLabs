import java.util.Scanner;

public class a {

    public static void main(String[] args) {

        Scanner scn = new Scanner(System.in);

        int a, b, n;

        a = scn.nextInt();
        b = scn.nextInt();
        n = scn.nextInt();

        int distance = (int) (2 * Math.ceil((double) (n - b) / (b - a)) + 1);

        System.out.println(distance);
    }




}
