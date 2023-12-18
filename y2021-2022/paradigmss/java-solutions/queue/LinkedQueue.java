package queue;

import java.util.Objects;

// Model: a[l] ... a[r - 1]
// Invariant: for i = l ... r - 1: a[i] != null

// Let immutuable (l, r): for i = l ... r - 1: a'[i] == a[i]

public class LinkedQueue extends AbstractQueue {
    private class Node {
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

    private Node first;
    private Node last;
    private Node startNode;


    // Pred: true
    // Post: r' = r + 1  && a[r' - 1] == element && l' = l && immutuable(l, r' - 1) && size' = size + 1
    // saveInQueue (element)

    @Override
    protected void saveInQueue(Object element) {
        last = new Node(last, element);
        if (size == 0) {
            first = last;
        }
    }


    // Pred: true
    // Post: R = a[l] && immutuable (l', r') && size' = size && r' = r && l' = l
    // getNowElement()
    @Override
    public Object getNowElement() {
        return first.element;
    }
    // Pred: true
    // Post: R = a[l' - 1] && l' = l + 1 && immutuable (l', r) && r' = r && size' = size - 1
    // delNowElement()

    @Override
    protected void delNowElement() {
        first.element = null;
        first = first.pred;
    }


    // Pred: true
    // Post: for i = l ... r - 1 a'[i] == null && r' = 0 && l' = 0 && size' = 0
    // partClear()
    @Override
    protected void partClear() {
        first = null;
        last = null;
    }

    //Pred: true
    //Post: startSearch = size - 1 && immutuable(l, r) && l' = l && r' = r && size' = size
    // startEndSearch()

    @Override
    public void startEndSearch() {
        startNode = last;
    }

    //Pred: true
    //Post: R = a[startSearch + l] && startSearch' = startSearch - 1 && immutuable(l, r)
    // && l' = l && r' = r && size' = size
    // nextForEndSearch()
    @Override
    public Object nextForEndSearch() {
        Object ret =  startNode.element;
        startNode = startNode.next;
        return ret;
    }


    //Pred: true
    //Post: startSearch = 0 && immutuable(l, r) && l' = l && r' = r && size' = size
    // startBeginSearch()

    @Override
    public void startBeginSearch() {
        this.startNode = this.first;

    }

    //Pred: true
    //Post: R = a[startSearch + l] && startSearch' = startSearch + 1 && immutuable(l, r)
    // && l' = l && r' = r && size' = size
    // nextForBeginSearch()
    @Override
    public Object nextForBeginSearch() {
        Object ret =  startNode.element;
        startNode = startNode.pred;
        return ret;
    }

}
