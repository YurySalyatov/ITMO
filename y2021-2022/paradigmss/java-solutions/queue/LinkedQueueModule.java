package queue;

import java.util.Objects;

    // Model: a[l] ... a[r - 1]
    // Invariant: for i = l ... r - 1: a[i] != null

    // Let immutuable (l, r): for i = l ... r - 1: a'[i] == a[i]

public class LinkedQueueModule {
    private static class Node {
        private Object element;
        private Node pred;
        private Node next;
        public Node(Node next, Object element) {
            this.next = next;
            if (next != null) {
                next.pred = this;
            }
            this.element = element;
        }
    }

    private static Node first;
    private static Node last;
    private static int size = 0;

    // Pred: element != null
    // Post: r' = r + 1 && a[r' - 1] == element && immutuable(l, r') && size' = size + 1
    // enqueue (element)

    public static void enqueue(Object element) {
        Objects.requireNonNull(element);
        last = new Node(last, element);
        if (size == 0) {
            first = last;
        }
        size++;
    }

    // Pred: size != 0
    // Post: R = a[l] && immutuable (l', r) && size' = size && r' = r && l' = l
    // element()

    public static Object element() {
        assert size != 0;
        return first.element;
    }
    // Pred: size != 0
    // Post: R = a[l' - 1 % a.length] && l' = l + 1 % a.length && immutuable (l', r) && r' = r && size' = size - 1
    // dequeue()

    public static Object dequeue() {
        assert size != 0;
        Object ret = first.element;
        first = first.pred;
        size--;
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
        first = null;
        last = null;
        size = 0;
    }

    //Pred: element != null
    //Post: R = -1 || k: a[k] == element && for i k + 1 ... r - 1 a[i] != element

    public static int lastIndexOf(Object element) {
        int ret = -1;
        int k = size - 1;
        Node search = last;
        while (k >= 0) {
            if (element.equals(search.element)) {
                ret = k;
                break;
            }
            k--;
            search = search.next;
        }
        return ret;
    }

    //Pred: element != null
    //Post: R = -1 || k: a[k] == element && for i l ... k - 1 a[i] != element

    public static int indexOf(final Object element) {
        int ret = -1;
        int k = 0;
        Node search = first;
        while (k < size) {
            if (element.equals(search.element)) {
                ret = k;
                break;
            }
            k++;
            search = search.pred;
        }
        return ret;
    }
}
