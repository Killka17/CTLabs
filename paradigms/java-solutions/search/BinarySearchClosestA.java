package search;

public class BinarySearchClosestA {
    //Pre: ( args.length() >= 2 && for a in args: MIN_INT <= int(a) <= MAX_INT && args.length() -> int ) = P
    //Post: R (abs(arr[R] - x) -> min)

    public static void main(String[] args) {
        //P
        int numb = Integer.parseInt(args[0]);
        //P && numb = int(args[0])
        int sum = 0;
        //P && numb = int(args[0]) && sum = 0
        int[] subsequence = new int[args.length - 1];
        for (int i = 1; i < args.length; i++) {
            int number = Integer.parseInt(args[i]);
            subsequence[i - 1] = number;
            // :NOTE: overflow
            sum += number;
        }
        //( numb = int(args[0]) && sum = sum(int(x) for x in subsequence) && subsequence = args[1:] && a -> int for all a in subsequence ) = I
        if (sum % 2 == 0) {
            // ( I && sum % 2 == 0 ) -> start Recursive search
            System.out.println(RecursiveBinarySearch(numb, subsequence, -1, subsequence.length));
        } else {
            // ( I && sum % 2 != 0 ) -> start Binary search
            System.out.println(IterativeBinarySearch(numb, subsequence));
        }

    }


    // Pre: x -> int && arr -> [a1, a2, ....., an] && ai -> int && ai-1 <= ai
    // Post: return res: res in subsequence, abs(res - x) -> min for all res in subsequence
    // :NOTE: naming: iter...
    private static int IterativeBinarySearch(int x, int[] subsequence) {
        int l = -1;
        //P: True
        int r = subsequence.length;
        //l == -1 && r = subsequence.length && r > 0 && r > l
        //P: r - l > 1
        int mid = l + (r - l) / 2;
        //Q: l == -1 && r = subsequence.length && mid == l + (r - l) // 2
        //I: r' - l' < r - l && r - l > 1 && subsequence[l'] <= subsequence[mid'] <= subsequence[r']
        while (1 < r - l) {
            // I
            if (subsequence[mid] < x) {
                // I && mid < r
                l = mid;
                // I && l' < r' && l' = mid
            } else {
                //I && mid >= x
                r = mid;
                // I && r' = mid
            }
            // r' - l' < r - l && r - l > 1
            mid = l + (r - l) / 2;
            // r' - l' < r - l && r - l > 1 && mid = l + (r - l) / 2 -> subsequence[l'] <= subsequence[mid'] <= subsequence[r']
        }
        //if x < a for a in subsequence -> r' = 0
        // else if x > a for a in subsequence -> r' = subsequence.length
        // else (subsequence[l'] > x && subsequence[r'] <= x && r' - l' <= 1) -> r' = min i: ai <= x
        if (r == 0)
            // (subsequence[r - 1] == null && subsequence[r + 1] >= subsequence[r] && x < a for all a in subsequence) ->
            // -> return res: res in subsequence, abs(res - x) -> min for all res in subsequence
            return subsequence[r];
        else if (l == subsequence.length - 1)
            //r == subsequence.length -> x > a for all a in subsequence ->
            // -> return res: res in subsequence, abs(res - x) -> min for all res in subsequence
            return subsequence[l];
        else {
            // subsequence[r - 1] != null && subsequence[r + 1] != null
            // r = min i: ai <= x
            if (Math.abs(subsequence[l] - x) <= Math.abs(subsequence[r] - x))
                return subsequence[l];
            return subsequence[r];
            // непосредственно сравниваем разницу, если элементы слева и справа от r существуют
            // subsequence[r - 1] < subsequence[r] <= subsequence[r + 1] ->
            // -> return res: res in subsequence, abs(res - x) -> min for all res in subsequence
        }
    }


    // Pre: x -> int && arr -> [a1, a2, ....., an] && ai -> int && ai-1 <= ai && l >= 0 && l < r && r <= len(arr) - 1
    // Post: return res: res in subsequence, abs(res - x) -> min for all res in subsequence
    private static int RecursiveBinarySearch(int x, int[] subsequence, int l, int r) {
        //r - l >= 1
        int mid = l + (r - l) / 2;
        //r - l >= 1 && mid = l + (r - l) / 2;
        // r - l >= 1
        if (1 == r - l) {
            //if x < a for a in subsequence -> r = 0
            // else if x > a for a in subsequence -> r = subsequence.length
            // else (subsequence[l] > x && subsequence[r] <= x && r - l <= 1) -> r = min i: ai <= x
            if (r == 0)
                // (subsequence[r - 1] == null subsequence[r + 1] >= subsequence[r] && x < a for all a in subsequence) ->
                // -> return res: res in subsequence, abs(res - x) -> min for all res in subsequence
                return subsequence[r];
            else if (l == subsequence.length - 1)
                //r == subsequence.length -> x > a for all a in subsequence ->
                // -> return res: res in subsequence, abs(res - x) -> min for all res in subsequence
                return subsequence[l];
            else {
                // subsequence[r - 1] != null && subsequence[r + 1] != null
                // r = min i: ai <= x
                if (Math.abs(subsequence[l] - x) <= Math.abs(subsequence[r] - x))
                    return subsequence[l];
                return subsequence[r];
                // непосредственно сравниваем разницу, если элементы слева и справа от  r  существуют
                // subsequence[r - 1] < subsequence[r] <= subsequence[r + 1] ->
                // -> return res: res in subsequence, abs(res - x) -> min for all res in subsequence
            }
        }
        //r - l > 1 && mid = l + (r - l) / 2

        if (subsequence[mid] >= x) {
            // mid < r && subsequence[mid] >= x -> you should search in the left half of array, because subsequence[i - 1] <= subsequence[i] for all i
            return RecursiveBinarySearch(x, subsequence, l, mid);

        } else {
            // mid > l && subsequence[mid] < x -> you should search in the right half of array, because subsequence[i - 1] <= subsequence[i] for all i
            return RecursiveBinarySearch(x, subsequence, mid, r);
        }
    }
}
