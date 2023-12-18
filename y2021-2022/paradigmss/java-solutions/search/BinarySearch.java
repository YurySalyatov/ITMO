package search;

public class BinarySearch {
    // Pred: a.length > 0 && a.sort(more -> less)
    // ((any)∀ n > a[0] -> a[-1] = n) && ((any)∀ e < a[a.length - 1] -> a[a.length] = e)
    // Post: R, (a[R] <= x && x < a[R - 1] && R >= 0 && R <= a.length)
    public static int binarySearchIter(int x, int[] a) {
        // Pred -> P1
        int l = -1;
        // Q1: a[l] > x
        // P2: true
        int r = a.length;
        // Q2: a[r] <= x && r > l
        // Q1 && Q2 -> I
        // I: a[l] > x && a[r] <= x && r' > l'
        while (r - l > 1) {
            // a[l'] > x && a[r'] <= x && r' - l' > 1
            // P3: r' - l' > 1
            int m = (r + l) / 2;
            // Q3: l' <= m < r'
            // l' <= m < r' && a[l'] > x && a[r'] <= x && r' - l' > 1
            if (x < a[m]) {
                // P4: x < a[m]
                l = m;
                // Q4: x < a[l']  
            } else {
                // P5: x >= a[m] 
                r = m;
                // Q5: x >= a[r']

            }
            // Q4 -> I
            // Q5 -> I
            // I: a[l'] > x && a[r'] <= x && r' - l' > 1
        }
        // I: a[l'] > x && a[r'] <= x && r' > l' && r' - l' <= 1
        return r;
    }
    // Pred: a.length > 0 && a.sort(more -> less) && r > l && r <= a.length && l >= -1 && a[l] < x && x <= a[r]
    // ((any)∀ n > a[0] -> a[-1] = n) && ((any)∀ e < a[a.length - 1] -> a[a.length] = e)
    // Post: R (a[R] <= x && a[R- 1] > x && R >= 0 && R <= a.length)
    public static int binarySearchRec(int x, int[] a, int l, int r) {
        // Pred -> P1
        if (r - l < 2) {
            // P2: r > l %% r <= l + 1
            return r;
            // Q2: R
        }
        // Pred && (r - l > 1) -> P3
        int m = (r + l) / 2;
        // Q3: Pred && (r - l > 1) && l <= m < r
        if (x < a[m]) {
            // P4: Pred && (r - l > 1) && l <= m < r && x < a[m]
            return binarySearchRec(x, a, m, r);
            // Q4: R - min index
        } else {
            // P5: Pred && (r - l > 1) && l <= m < r&& x >= a[m]
            return binarySearchRec(x, a, l, m);
            // Q5: R - min index
        }
        // Q4 -> Q3
        // Q5 -> Q3
        // Q3: R - min index
    }
    // Pred: args.length > 0
    // Post: min index
    public static void main(String[] args) {
        int x = Integer.parseInt(args[0]);
        int[] a = new int[args.length - 1];
        for (int i = 0; i < args.length - 1; i++) {
            a[i] = Integer.parseInt(args[i + 1]);
        }
        //P: a.sort(more -> less)
        if (a.length != 0) {
            // P1: a.length > 0 && a.sort(more -> less)
            // System.out.println(binarySearchIter(x, a));
            System.out.println(binarySearchRec(x, a, -1, a.length));
            // Q1: a[R] <= x && R - min index
        } else {
            // P2: a.length == 0
            System.out.println(0);
            // Q2: 0 - min index
        }
        // Q1 -> Q
        // Q2 -> Q
        // Q: ind
    }
}
