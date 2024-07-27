import java.util.Scanner;

public class I {
    
    public static void main(String[] args) {

        Scanner scn = new Scanner(System.in);
        int n = scn.nextInt();
        int[] listX = new int[n];
        int[] listY = new int[n];
        int[] listH = new int[n];

        for (int i = 0; i < n; i++) {
            listX[i] = scn.nextInt();
            listY[i] = scn.nextInt();
            listH[i] = scn.nextInt();
        }
        
        int xl = 99999999;
        int xr = 0;
        int yl = 99999999;
        int yr = 0;

        for (int i = 0; i < n; i++) {
            xl = Math.min(listX[i] - listH[i], xl);
            xr = Math.max(listX[i] + listH[i], xr);

        }

        for (int i = 0; i < n; i++) {

            yl = Math.min(listY[i] - listH[i], yl);
            yr = Math.max(listY[i] + listH[i], yr);

        }

        int x_res = (xl + xr) / 2;
        int y_res = (yl + yr) / 2;
        int h_res = (int) Math.ceil((double) Math.max(xr - xl, yr - yl) / 2);

        System.out.print(x_res);
        System.out.print(" ");
        System.out.print(y_res);
        System.out.print(" ");
        System.out.print(h_res);

    }
}
