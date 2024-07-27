import java.util.Scanner;

public class b {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        long numb = -710 * 25000;

        System.out.println(numb);

        for (int i = 1; i < n; i++) {

            numb += 710;
            System.out.println(numb);

        }

    }
}
