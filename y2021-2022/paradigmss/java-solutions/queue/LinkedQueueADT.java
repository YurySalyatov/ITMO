package queue;

import java.util.Objects;

// Model: a[l] ... a[r - 1]
// Invariant: for i = l ... r - 1: a[i] != null

// Let immutuable (l, r): for i = l ... r - 1: a'[i] == a[i]

public class LinkedQueueADT {
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

    public static void enqueue(LinkedQueueADT queue, Object element) {
        Objects.requireNonNull(element);
        queue.last = new Node(queue.last, element);
        if (queue.size == 0) {
            queue.first = queue.last;
        }
        size++;
    }

    // Pred: size != 0
    // Post: R = a[l] && immutuable (l', r) && size' = size && r' = r && l' = l
    // element()

    public static Object element(LinkedQueueADT queue) {
        assert queue.size != 0;
        return queue.first.element;
    }
    // Pred: size != 0
    // Post: R = a[l' - 1 % a.length] && l' = l + 1 % a.length && immutuable (l', r) && r' = r && size' = size - 1
    // dequeue()

    public static Object dequeue(LinkedQueueADT queue) {
        assert queue.size != 0;
        Object ret = queue.first.element;
        queue.first = queue.first.pred;
        queue.size--;
        return ret;
    }

    // Pred: true
    // Post: R = size
    // size()

    public static int size(LinkedQueueADT queue) {
        return queue.size;
    }

    // Pred: true
    // Post: R = (size == 0)
    // iEmpty()

    public static boolean isEmpty(LinkedQueueADT queue) {
        return queue.size == 0;
    }

    // Pred: true
    // Post: for i = 0 ... a'.length - 1 a'[i] == null && r' = 0 && l' = 0 && size = 0
    // clear()

    public static void clear(LinkedQueueADT queue) {
        queue.first = null;
        queue.last = null;
        queue.size = 0;
    }

    //Pred: element != null
    //Post: R = -1 || k: a[k] == element && for i k + 1 ... r - 1 a[i] != element

    public static int lastIndexOf(LinkedQueueADT queue, final Object element) {
        int ret = -1;
        int k = queue.size - 1;
        Node search = queue.last;
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

    public static int indexOf(LinkedQueueADT queue, final Object element) {
        int ret = -1;
        int k = 0;
        Node search = queue.first;
        while (k < queue.size) {
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
