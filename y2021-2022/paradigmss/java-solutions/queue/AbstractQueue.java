package queue;

    // Model: a[l] ... a[r - 1]
    // Invariant: for i = l ... r - 1: a[i] != null

    // Let immutuable (l, r): for i = l ... r - 1: a'[i] == a[i]


import java.util.Objects;
import java.util.function.Predicate;

public abstract class AbstractQueue implements Queue {

    protected int size;

    // Pred: element != null
    // Post: r' = r + 1 && a[r' - 1] = element && immutuable(l, r') && size' = size + 1
    // enqueue (element)

    abstract void saveInQueue(Object element);

    public void enqueue(final Object element){
        Objects.requireNonNull(element);
        saveInQueue(element);
        size++;
    }

    // Pred: size != 0
    // Post: R = a[l] && immutuable (l', r) && size' = size && r' = r && l' = l
    // element()
    abstract Object getNowElement();
    public Object element() {
        assert size != 0;
        return getNowElement();
    }



    // Pred: size != 0
    // Post: R = a[l' - 1] && l' = l + 1 && immutuable (l', r) && r' = r && size' = size - 1
    // dequeue()
    abstract void delNowElement();
    public Object dequeue(){
        assert size != 0;
        Object ret = getNowElement();
        delNowElement();
        size--;
        return ret;
    }



    // Pred: true
    // Post: R = size && immutuable (l', r) && size' = size && r' = r && l' = l
    // size()

    public int size(){
        return size;
    }


    // Pred: true
    // Post: R = (size == 0) && immutuable (l', r) && size' = size && r' = r && l' = l
    // iEmpty()

    public boolean isEmpty(){
        return size == 0;
    }

    abstract void partClear();

    // Pred: true
    // Post: for i = l ... r - 1 a'[i] == null && r' = 0 && l' = 0 && size = 0
    // clear()
    public void clear(){
        size = 0;
        partClear();
    }

    abstract void startEndSearch();
    abstract Object nextForEndSearch();

    //Pred: predicate != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && predicate.test(a[i]) == false)
    // || (k: predicate.test(a[k]) == true && for i: k + 1 ... r - 1: predicate.test(a[i]) == false)
    // && immutuable (l, r) && size' = size && r' = r && l' = l
    public int lastIndexIf(Predicate<Object> pred) {
        int ret = -1;
        int k = size - 1;
        startEndSearch();
        while (k >= 0) {
            if (pred.test(nextForEndSearch())) {
                ret = k;
                break;
            }
            k--;
        }
        return ret;
    }

    //Pred: predicate != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && predicate.test(a[i]) == false)
    // || (k: predicate.test(a[k]) == true && for i: l ... k - 1: predicate.test(a[i]) == false)
    // && immutuable (l, r) && size' = size && r' = r && l' = l

    abstract void startBeginSearch();
    abstract Object nextForBeginSearch();
    public int indexIf(Predicate<Object> pred) {
        int ret = -1;
        int k = 0;
        startBeginSearch();
        while (k < size) {
            if (pred.test(nextForBeginSearch())) {
                ret = k;
                break;
            }
            k++;
        }
        return ret;
    }

    //Pred: element != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && a[i] != element)
    // || (k: a[k] == element && for i: k + 1 ... r - 1: a[i] != element)
    // && immutuable (l, r) && size' = size && r' = r && l' = l

    public int lastIndexOf(Object element) {
        int ret = -1;
        int k = size - 1;
        startEndSearch();
        while (k >= 0) {
            if (element.equals(nextForEndSearch())) {
                ret = k;
                break;
            }
            k--;
        }
        return ret;
    }

    //Pred: element != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && a[i] != element)
    // || (k: a[k] == element && for i: l ... k - 1: a[i] != element)
    // && immutuable (l, r) && size' = size && r' = r && l' = l

    public int indexOf(Object element) {
        // :NOTE: copypaste
        int ret = -1;
        int k = 0;
        startBeginSearch();
        while (k < size) {
            if (element.equals(nextForBeginSearch())) {
                ret = k;
                break;
            }
            k++;
        }
        return ret;
    }
}
