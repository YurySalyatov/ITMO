package queue;


    // Model: a[1] ... a[n]
    // Invariant: for i = l ... r - 1 % a.length: a[i] != null

    // Let immutuable (l, r): for i = l ... r - 1 % a.length: a'[i] == a[i]

import java.util.Objects;

public class ArrayQueueModule {

    private static int r = 0;
    private static int l = 0;
    private static int size = 0;
    private static Object[] elements = new Object[2];

    // Pred: element != null
    // Post: r' = r + 1 % a.lenth && a[r - 1 % a.length] == element && immutuable(l, r') && size' = size + 1
        // enqueue (element)
    
    public static void enqueue(Object element) {
        Objects.requireNonNull(element);
        elements[r] = element;
        size++;
        r = (r + 1) % elements.length;
        chekQueue();
    }

    private static void chekQueue() {
        if (size == elements.length) {
            arrayBigger();
        }
    }

    private static void arrayBigger() {
        Object[] el = new Object[elements.length * 2];
        // :NOTE: system.arraycopy
        for (int i = l; i < elements.length; i++) {
            el[i - l] = elements[i];
        }
        for (int i = 0; i < r; i++) {
            el[elements.length - l + i] = elements[i];
        }
        r = elements.length;
        l = 0;
        elements = el;
        el = null;
    }
    // Pred: size != 0
    // Post: R = a[l] && immutuable (l', r) && size' = size && r' = r && l' = l
        // element()

    public static Object element() {
        assert size != 0;
        return elements[l];
    }
    // Pred: size != 0
    // Post: R = a[l' - 1 % a.length] && l' = l + 1 % a.length && immutuable (l', r) && r' = r && size' = size - 1
        // dequeue()
    
    public static Object dequeue() {
        assert size != 0;
        Object ret = elements[l];
        elements[l] = null;
        size--;
        l = (l + 1) % elements.length;
        return ret;
    }

    // Pred: true
    // Post: R = size
        // size()

    public static int size() {
        return size;
    }

    // Pred: true
    // Post: R = (size == 0) 
        // iEmpty()

    public static boolean isEmpty() {
        return size == 0;
    }

    // Pred: true
    // Post: for i = 0 ... a'.length - 1 a'[i] == null && r' = 0 && l' = 0 && size = 0
        // clear()

    public static void clear() {
        while (!isEmpty()) {
            dequeue();
        }
        l = 0;
        r = 0;
    }

    //Pred: element != null
    //Post: R = -1 || k: a[k] == element && for i k + 1 ... r - 1 a[i] != element

    public static int lastIndexOf(Object element) {
        int ret = -1;
        int k = size - 1;
        while (k >= 0) {
            if (elements[(k + l) % elements.length].equals(element)) {
                ret = k;
                break;
            }
            k--;
        }
        return ret;
    }

    //Pred: element != null
    //Post: R = -1 || k: a[k] == element && for i l ... k - 1 a[i] != element

    public static int indexOf(final Object element) {
        int ret = -1;
        int k = 0;
        while (k < size) {
            if (elements[(k + l) % elements.length].equals(element)) {
                ret = k;
                break;
            }
            k++;
        }
        return ret;
    }

}
