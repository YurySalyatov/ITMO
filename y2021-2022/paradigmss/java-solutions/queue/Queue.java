package queue;

import java.util.function.Predicate;

public interface Queue {
    // Model: a[l] ... a[r - 1]
    // Invariant: for i = l ... r - 1: a[i] != null

    // Let immutuable (l, r): for i = l ... r - 1: a'[i] == a[i]


    // Pred: element != null
    // Post: r' = r + 1 && a'[r' - 1] = element && immutuable(l, r) && size' = size + 1
    // enqueue (element)


    void enqueue(final Object element);

    // Pred: size != 0
    // Post: R = a[l] && immutuable (l', r) && size' = size && r' = r && l' = l
    // element()

    Object element();


    // Pred: size != 0
    // Post: R = a[l] && l' = l + 1 && immutuable (l', r) && r' = r && size' = size - 1
    // dequeue()

    Object dequeue();


    // Pred: true
    // Post: R = size
    // size()

    int size();


    // Pred: true
    // Post: R = (size == 0)
    // iEmpty()

    boolean isEmpty();


    // Pred: true
    // Post: for i = l ... r - 1 a'[i] == null && r' = 0 && l' = 0 && size' = 0
    // clear()

    void clear();


    //Pred: predicate != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && predicate.test(a[i]) == false)
    // || (k: predicate.test(a[k]) == true && for i: k + 1 ... r - 1: predicate.test(a[i]) == false)
    // && immutuable (l, r) && size' = size && r' = r && l' = l

    int lastIndexIf(Predicate<Object> pred);


    //Pred: predicate != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && predicate.test(a[i]) == false)
    // || (k: predicate.test(a[k]) == true && for i: l ... k - 1: predicate.test(a[i]) == false)
    // && immutuable (l, r) && size' = size && r' = r && l' = l

    int indexIf(Predicate<Object> pred);


    //Pred: element != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && a[i] != element)
    // || (k: a[k] == element && for i: k + 1 ... r - 1: a[i] != element)
    // && immutuable (l, r) && size' = size && r' = r && l' = l

    int lastIndexOf(Object element);


    //Pred: element != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && a[i] != element)
    // || (k: a[k] == element && for i: l ... k - 1: a[i] != element)
    // && immutuable (l, r) && size' = size && r' = r && l' = l

    int indexOf(Object element);
}
