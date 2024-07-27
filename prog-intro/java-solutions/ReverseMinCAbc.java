import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;





public class ReverseMinCAbc {

    public static boolean isNegative(String number) {
        return number.charAt(0) == '-';
    }

    public static boolean isNegativeSmaller(String lhs, String rhs) {

        if (lhs.length() < rhs.length() ) {
            return false;
        } else if (lhs.length() > rhs.length()) {
            return true;
        } else {

            for (int i = 0; i < lhs.length(); ++i) {

                if (lhs.charAt(i) - 'a' < rhs.charAt(i) - 'a') {
                    return false;
                }
                if (lhs.charAt(i) - 'a' > rhs.charAt(i) - 'a') {
                    return true;
                }
            }

            return true;
        }

    }

    public static boolean isSmaller(String lhs, String rhs) {

        if (isNegative(lhs) && !isNegative(rhs)) return true;

        if (!isNegative(lhs) && isNegative(rhs)) return false;

        if (isNegative(lhs) && isNegative(rhs))
            return isNegativeSmaller(lhs, rhs);


        if (lhs.length() < rhs.length() ) {
            return true;
        } else if (lhs.length() > rhs.length()) {
            return false;
        } else {

            for (int i = 0; i < lhs.length(); ++i) {

                if (lhs.charAt(i) - 'a' > rhs.charAt(i) - 'a') {
                    return false;
                }
                if (lhs.charAt(i) - 'a' < rhs.charAt(i) - 'a') {
                    return true;
                }
            }

            return true;
        }

    }

    public static void main(String[] args) throws IOException {

        MyScanner scanner = new MyScanner();
        ArrayList<String> list = new ArrayList<>();
        List_forward list2 = new List_forward();

        String maxValue = "a";
        int maxRowNums = 0;

        while (scanner.nextLine()) {
            int rowNums = 0;

            while (scanner.hasNextChar()) {

                String digit = scanner.nextCharSubstr();
                if (isSmaller(maxValue, digit)) {
                    maxValue = digit;
                }

                list.add(digit);
                rowNums++;
            }
            list2.append(rowNums);
            if (maxRowNums < rowNums) {
                maxRowNums = rowNums;
            }
        }

        String[] minInt = new String[maxRowNums];
        Arrays.fill(minInt, maxValue);

        int k = 0;
        int i = 0;

        while (k < list2.vector.length && list2.vector[k] != null) {
            if (list2.vector[k] == 0) {
                System.out.print("\n");

            } else {
                int j = 0;
                for (int m = 0; m < list2.vector[k]; m++) {
                    if (isSmaller(list.get(i), minInt[j])) {
                        minInt[j] = list.get(i);
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
