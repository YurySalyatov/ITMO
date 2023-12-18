package queue;


    // Model: a[l] ... a[r - 1]
    // Invariant: for i = l ... r - 1: a[i] != null

    // Let immutuable (l, r): for i = l ... r - 1: a'[i] == a[i]
    
public class ArrayQueue extends AbstractQueue {

    private int r = 0;
    private int l = 0;
    private Object[] elements = new Object[2];
    private int startSearch;

    // Pred: true
    // Post: r' = r + 1  && a[r' - 1] == element && l' = l && immutuable(l, r' - 1) && size' = size + 1
        // saveInQueue (element)

    @Override
    protected void saveInQueue(Object element) {
        elements[r] = element;
        r = (r + 1) % elements.length;
        chekQueue();
    }


    private void chekQueue() {
        if (r == l) {
            arrayBigger();
        }
    }

    private void arrayBigger() {
        Object[] el = new Object[elements.length * 2];
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
    // Pred: true
    // Post: R = a[l] && immutuable (l', r') && size' = size && r' = r && l' = l
        // getNowElement()
    @Override
    protected Object getNowElement() {
        return elements[l];
    }
    // Pred: true
    // Post: R = a[l' - 1] && l' = l + 1 && immutuable (l', r) && r' = r && size' = size - 1
        // delNowElement()

    @Override
    protected void delNowElement() {
        elements[l] = null;
        l = (l + 1) % elements.length;
    }



    // Pred: true
    // Post: for i = l ... r - 1 a'[i] == null && r' = 0 && l' = 0 && size' = 0
        // partClear()
    @Override
    protected void partClear() {
        l = 0;
        r = 0;
        elements = new Object[2];
    }

    //Pred: true
    //Post: startSearch = size - 1 && immutuable(l, r) && l' = l && r' = r && size' = size
    // startEndSearch()

    @Override
    protected void startEndSearch() {
        startSearch = size - 1;
    }

    //Pred: true
    //Post: R = a[startSearch + l] && startSearch' = startSearch - 1 && immutuable(l, r)
    // && l' = l && r' = r && size' = size
    // nextForEndSearch()
    @Override
    protected Object nextForEndSearch() {
        return elements[(startSearch-- + l) % elements.length];
    }


    //Pred: true
    //Post: startSearch = 0 && immutuable(l, r) && l' = l && r' = r && size' = size
    // startBeginSearch()

    @Override
    protected void startBeginSearch() {
        startSearch = 0;
    }

    //Pred: true
    //Post: R = a[startSearch + l] && startSearch' = startSearch + 1 && immutuable(l, r)
    // && l' = l && r' = r && size' = size
    // nextForBeginSearch()
    @Override
    protected Object nextForBeginSearch() {
        return elements[(startSearch++ + l) % elements.length];
    }

    //Pred: element != null
    //Post: R = (-1 && for i: l .. r - 1: a[i] && a[i] != element)
    // || (k: a[k] == element && for i: k + 1 ... r - 1: a[i] != element)
    // && immutuable (l, r) && size' = size && r' = r && l' = l
    @Override
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
    @Override
    public int indexOf(Object element) {
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
