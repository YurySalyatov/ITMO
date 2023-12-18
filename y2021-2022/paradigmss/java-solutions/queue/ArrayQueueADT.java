package queue;


    // Model: a[l] ... a[r - 1]
    // Invariant: for i = l ... r - 1: a[i] != null

    // Let immutuable (l, r): for i = l ... r - 1: a'[i] == a[i]

import java.util.Objects;

public class ArrayQueueADT {

    // :NOTE: ADT should be different from Module
    private static int r;
    private static int l;
    private static int size;
    private static Object[] elements = new Object[2];


    // Pred: element != null && queue != null
    // Post: r' = r + 1 && a[r' - 1] = element && immutuable(l, r') && size' = size + 1
    // enqueue (element)
    
    public static void enqueue(ArrayQueueADT queue, Object element) {
        assert element != null;
//        assert queue.elements != null;
        queue.elements[queue.r] = element;
        queue.size++;
        queue.r = (queue.r + 1) % queue.elements.length;
        chekQueue(queue);
    }

    private static void chekQueue(ArrayQueueADT queue) {
        if (queue.size == queue.elements.length) {
            arrayBigger(queue);
        }
    }

    private static void arrayBigger(ArrayQueueADT queue) {
        Object[] el = new Object[queue.elements.length * 2];
        for (int i = queue.l; i < queue.elements.length; i++) {
            el[i - queue.l] = queue.elements[i];
        }
        for (int i = 0; i < r; i++) {
            el[queue.elements.length - queue.l + i] = queue.elements[i];
        }
        queue.r = queue.elements.length;
        queue.l = 0;
        queue.elements = el;
        el = null;
    }
    // Pred: size != 0 && queue != null
    // Post: R = a[l] && immutuable (l', r) && size' = size && r' = r && l' = l
    // element()

    public static Object element(ArrayQueueADT queue) {
//        assert Objects.isNull();
        assert queue.size != 0;
        return queue.elements[queue.l];
    }
    // Pred: size != 0 && queue != null
    // Post: R = a[l' - 1] && l' = l + 1 && immutuable (l', r) && r' = r && size' = size - 1
    // dequeue()
    
    public static Object dequeue(ArrayQueueADT queue) {
        assert queue.size != 0;
        Object ret = queue.elements[queue.l];
        queue.elements[queue.l] = null;
        queue.size--;
        queue.l = (queue.l + 1) % queue.elements.length;
        return ret;
    }

    // Pred: queue != null
    // Post: R = size && immutuable(l, r) && r' = r && l' = l && size' = size
    // size()

    public static int size(ArrayQueueADT queue) {
        return queue.size;
    }

    // Pred: true
    // Post: R = (size == 0) && immutuable (l', r) && size' = size && r' = r && l' = l
    // iEmpty()

    public static boolean isEmpty(ArrayQueueADT queue) {
        return queue.size == 0;
    }

    // Pred: true
    // Post: for i = l ... r - 1 a'[i] == null && r' = 0 && l' = 0 && size = 0
    // clear()

    public static void clear(ArrayQueueADT queue) {
        queue.elements = new Object[2];
        queue.r = 0;
        queue.l = 0;
        queue.size = 0;
    }

    //Pred: element != null && queue != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && a[i] != element)
    // || (k: a[k] == element && for i: k + 1 ... r - 1: a[i] != element)
    // && immutuable (l, r) && size' = size && r' = r && l' = l

    public static int lastIndexOf(ArrayQueueADT queue, Object element) {
        int ret = -1;
        int k = queue.size - 1;
        while (k >= 0) {
            if (queue.elements[(k + queue.l) % queue.elements.length].equals(element)) {
                ret = k;
                break;
            }
            k--;
        }
        return ret;
    }

    //Pred: element != null && queue != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && a[i] != element)
    // || (k: a[k] == element && for i: l ... k - 1: a[i] != element)
    // && immutuable (l, r) && size' = size && r' = r && l' = l

    public static int indexOf(ArrayQueueADT queue, final Object element) {
        int ret = -1;
        int k = 0;
        while (k < queue.size) {
            if (queue.elements[(k + queue.l) % queue.elements.length].equals(element)) {
                ret = k;
                break;
            }
            k++;
        }
        return ret;
    }

}
