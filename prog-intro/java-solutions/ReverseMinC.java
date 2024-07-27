import java.io.IOException;
import java.util.Scanner;
import java.util.Arrays;

class List_forward{

    Integer[] vector = new Integer[2];
    int pointer = 0;

    public void append(Integer newInt){

        if (this.pointer == this.vector.length - 1) {
            Integer[] newVektor = new Integer[(this.pointer + 1) * 2];
            System.arraycopy(this.vector, 0, newVektor, 0, this.pointer + 1); //  Arrays.copyOf
            newVektor[this.pointer] = newInt;
            this.vector = newVektor;
        } else {
            this.vector[this.pointer] = newInt;
        }
        this.pointer++;
    }
}


public class ReverseMinC {

    public static void main(String[] args) throws IOException {

        MyScanner scanner = new MyScanner();
        List_forward list = new List_forward();
        List_forward list2 = new List_forward();

        int maxValue = 0;
        int maxRowNums = 0;

        while (scanner.nextLine()) {
            int rowNums = 0;

            while (scanner.hasNextInt()) {

                int digit = scanner.nextInt();
                if (digit > maxValue) {
                    maxValue = digit;
                }

                list.append(digit);
                rowNums++;
            }
            list2.append(rowNums);
            if (maxRowNums < rowNums) {
                maxRowNums = rowNums;
            }
        }

        int[] minInt = new int[maxRowNums];
        Arrays.fill(minInt, maxValue + 1);

        int k = 0;
        int i = 0;

        while (k < list2.vector.length && list2.vector[k] != null) {
            if (list2.vector[k] == 0) {
                System.out.print("\n");

            } else {
                int j = 0;
                for (int m = 0; m < list2.vector[k]; m++) {
                    if (list.vector[i] < minInt[j]) {
                        minInt[j] = list.vector[i];
                    }
                    System.out.print(minInt[j] + " ");
                    j++;
                    i++;
                }
                System.out.print("\n");
            }
            k++;
        }
    }
}
