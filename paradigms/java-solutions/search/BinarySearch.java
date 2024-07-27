package search;


public class BinarySearch {

    //Pre: args.length() >= 1 && for a in args: MIN_INT <= int(a) <= MAX_INT && args.length() -> int
    //Post: R (arr[R] <= x && R >= 0 && R -> min)
    //      0 if x > a for a in subsequence
    //      subsequence.length if x < a for a in subsequence
    public static void main(String[] args) {
        int numb = Integer.parseInt(args[0]);
        int sum = 0;
        int[] subsequence = new int[args.length - 1];
        for (int i = 1; i < args.length; i++) {
            int number = Integer.parseInt(args[i]);
            subsequence[i - 1] = number;
            sum += number;
        }
        if (sum % 2 == 0) {
            System.out.println(RecursiveBinarySearch(numb, subsequence, -1, subsequence.length));
        } else {
            System.out.println(IterativeBinarySearch(numb, subsequence));
        }

    }


    // Pre: x -> int && arr -> [a1, a2, ....., an] && ai -> int && ai-1 >= ai
    // Post: R (arr[R] <= x && R >= 0 && R -> min)
    // 0 if x > a for a in subsequence
    // subsequence.length if x < a for a in subsequence
    private static int IterativeBinarySearch(int x, int[] subsequence) {
        int l = -1;
        //Q: x -> int && subsequence -> [a1, a2, ....., an] && ai -> int && ai-1 >= ai && l == -1
        //P: True
        int r = subsequence.length;
        //Q: x -> int && subsequence -> [a1, a2, ....., an] && ai -> int && ai-1 >= ai && l == 0 && r = subsequence.length && r > 0
        //P: r - l > 1
        int mid = l + (r - l) / 2;
        //Q: x -> int && subsequence -> [a1, a2, ....., an] && ai -> int && ai-1 >= ai && l == 0 &&
        // r = subsequence.length && mid == l + (r - l) // 2
        //I: r' - l' < r - l && r - l > 1 && subsequence[l'] < subsequence[res] <= subsequence[r']
        while (1 < r - l) {
            // r' - l' < r - l && r - l > 1
            if (subsequence[mid] <= x) {
                // r' - l' < r - l && r - l > 1 && subsequence[mid] <= x && mid <= r
                r = mid;
                // r' - l' < r - l && r - l >= 1
            } else {
                // r' - l' < r - l && r - l > 1 && subsequence[mid] > x && mid < r
                l = mid;
                // r' - l' < r - l && r - l >= 1
            }
            // r' - l' < r - l && r - l > 1
            mid = l + (r - l) / 2;
            // r' - l' < r - l && r - l > 1 && mid = l + (r - l) / 2
        }
        //if x < a for a in subsequence -> return subsequence.length
        // else if x > a for a in subsequence -> return 0
        // else (subsequence[l] > x && subsequence[r] <= x && r - l <= 1) -> r - min i: ai <= x
        return r;
    }

    // Pre: (x -> int && arr -> [a1, a2, ....., an] && ai -> int && ai-1 >= ai && l -> int && l == -1 && r == subsequence.length && r -> int) == I;
    // Post: (arr[R] <= x && R >= 0 && R -> min)
    // 0 if x > a for a in subsequence
    // subsequence.length if x < a for a in subsequence
    private static int RecursiveBinarySearch(int x, int[] subsequence, int l, int r) {
        //r - l > 1
        int mid = l + (r - l) / 2;
        //r - l > 1 && mid = l + (r - l) / 2;
        // r - l >= 1
        if (1 == r - l) {
            //if x < a for a in subsequence -> r == subsequence.length, l == subsequence.length - 1
            // else if x > a for a in subsequence -> r == 0, l == -1
            // else (subsequence[l] > x && subsequence[r] <= x && r - l == 1) -> r == min i: ai <= x
            return r;
        }
        //r - l > 1 && mid = l + (r - l) / 2

        if (subsequence[mid] <= x) {
            // I && mid < r && subsequence[mid] <= x -> you should search in the left half of array
            return RecursiveBinarySearch(x, subsequence, l, mid);

        } else {
            // I && mid < r && subsequence[mid] > x -> you should search in the right half of array
            return RecursiveBinarySearch(x, subsequence, mid, r);
        }
    }
}