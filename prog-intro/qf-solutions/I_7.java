import java.util.Scanner;

public class I {
    
    public static void main(String[] args) {

        Scanner scn = new Scanner(System.in);
        int n = scn.nextInt();
        long[] listX = new long[n];
        long[] listY = new long[n];
        long[] listH = new long[n];

        for (int i = 0; i < n; i++) {
            listX[i] = scn.nextInt();
            listY[i] = scn.nextInt();
            listH[i] = scn.nextInt();
        }
        
        long xl = Long.MAX_VALUE;
        long xr = 0;
        long yl = Long.MAX_VALUE;
        long yr = 0;

        for (int i = 0; i < n; i++) {
            xl = Math.min(listX[i] - listH[i], xl);
            xr = Math.max(listX[i] + listH[i], xr);

        }

        for (int i = 0; i < n; i++) {

            yl = Math.min(listY[i] - listH[i], yl);
            yr = Math.max(listY[i] + listH[i], yr);

        }

        long x_res = (xl + xr) / 2;
        long y_res = (yl + yr) / 2;
        long h_res = (long) Math.ceil((double) Math.max((xr - xl), (yr - yl)) / 2);

        System.out.print(x_res);
        System.out.print(" ");
        System.out.print(y_res);
        System.out.print(" ");
        System.out.print(h_res);

    }
}
