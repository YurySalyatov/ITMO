package search;

/**
 * BinarySearchShift
 */
public class BinarySearchShift {
    // Pred: a.length > 0 && a.sort(less -> more, less -> more) && 
    //      && ((any)∀ 0 <= i, j <= a.length - 1 && i != j): a[i] != a[j] && 
    //      && (∃!(exist one) k: a[k] < a[k + 1] && (a[k] < a[k - 1] || k = 0))
    // Post: R: a[R] = min(a[i], 0 <= i < a.length)
    public static int binarySearchShiftIter(int[] a) {
        // P -> P1
        int l = -1;
        // Q1: true
        // P -> P2: a[a.length - 1] - exist
        int r = a.length - 1;
        // Q2: a[r] - exist

        // I: l' < r' && a[r'] - min(a[i] r' <= i <= a.length - 1 && 0 <= i <= l')
        while (r - l > 1) {
            // I: l' < r' && a[r'] - min(a[i] r' <= i <= a.length - 1 && 0 <= i <= l') && r - l > 1
            // P3: I && (r' > l' - > r' > (r' + l') / 2 >= l')
            int m = (r + l) / 2;
            // Q3: r' > m >= l' && I
            // Q3 -> P4
            if (a[r] < a[m]) {
                // P5: I && a[r'] < a[m] && a[r'] - min(a[i] r' <= i <= a.length - 1 && 0 <= i <= m)
                l = m;
                // Q5: I && a[r'] < a[l'] && a[r'] - min(a[i] r' <= i <= a.length - 1 && 0 <= i <= l')
            } else {
                // P6: I && a[r'] >= a[m] && a[m] - min(a[i] m <= i <= a.length - 1 && 0 <= i <= l')
                r = m;
                // Q6: I && a[r'] >= a[r'] && a[r'] - min(a[i] r' <= i <= a.length - 1 && 0 <= i <= l')
            }
            // Q5 -> Q4
            // Q6 -> Q4
            // Q4: l' < r' && a[r'] - min(a[i] r' <= i <= a.length - 1 && 0 <= i <= l')
        }
        // I: l' < r' && a[r'] - min(a[i] r' <= i <= a.length - 1 && 0 <= i <= l') && r - l < 2 -> 
        // -> a[r] = min (a[i], 0 <= i < a.length)
        return r;
    }
    // Pred: a.length > 0 && a.sort(more -> less, more -> less) && 
    //      && ((any)∀ 0 <= i, j <= a.length - 1 && i != j): a[i] != a[j] && 
    //      && (∃!(exist one) k: a[k] > a[R + 1] && (a[k] > a[R - 1] || k = 0))
    //      && a[r] = min(a[i], 0<= i <= l && r <= i < a.length)
    // Post: R: a[R] = min(a[i], 0 <= i < a.length)
    public static int binarySearchRec(int[] a, int l, int r) {
        if (r - l < 2) {
            // P && r - l < 2 -> a[r] = min(a[i], 0 <= i < a.length)
            return r;
        }
        // P1: P && r - l > 1
        int m = (l + r) / 2;
        // Q1: P && r > m >= l
        if (a[r] < a[m]) {
            // P2: P && a[r] < a[m] && a[r] - min(a[i] r <= i <= a.length - 1 && 0 <= i <= m)
            return binarySearchRec(a, m, r);
            // Q3: P && a[r] - min(a[i] r <= i <= a.length - 1 && 0 <= i <= l)
        } else {
            // P4: P && a[r] < a[m] && a[r] - min(a[i] m <= i <= a.length - 1 && 0 <= i <= l)
            return binarySearchRec(a, l, m);
            // Q4: P && a[r] < a[m] && a[r] - min(a[i] r <= i <= a.length - 1 && 0 <= i <= m)
        }
        // Q3 -> 
    }

    // Pred: args.length != 0
    // Post: true
    public static void main(String[] args) {
        // P -> P1: args <-> array string
        int[] a = new int[args.length];
        // Q1: a.length = array.length
        // P2: a.length = array.length
        for (int i = 0; i < a.length; i++) {
            a[i] = Integer.parseInt(args[i]);
        }
        // Q2: a <-> array int
        // P3: a.length != 0
        System.out.println(binarySearchShiftIter(a));
        //System.out.println(binarySearchRec(a, -1, a.length - 1));
        // Q4: shift array
    }
}