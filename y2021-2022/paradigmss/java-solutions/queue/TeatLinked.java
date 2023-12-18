package queue;

public class TeatLinked {
    public static void main(String[] args) {
        LinkedQueue queue = new LinkedQueue();
        queue.enqueue("1");
        queue.enqueue("2");
        queue.enqueue("3");
        System.out.println(queue.element());
        System.out.println(queue.dequeue());
        System.out.println(queue.element());
        queue.startBeginSearch();
        System.out.println(queue.element());
        queue.nextForBeginSearch();
        System.out.println(queue.dequeue());
        queue.startBeginSearch();
    }
//        System.out.println("1 string");
//        LinkedQueue queue = new LinkedQueue();
//        for (int i = 0; i < 10; i++) {
//            queue.enqueue("element " + (i + 1));
//        }
//        System.out.println("2 string");
//        for (int i = 10; i > 0; i--) {
//            queue.enqueue("element " + i);
//        }
//        System.out.println("3 string");
//        int k = 0;
//        System.out.println("4 string");
//        while (!queue.isEmpty()) {
//            Object x = queue.dequeue();
//            System.out.println(k + " " + x);
//            k++;
//        }
//
//        System.out.println("5 string");
//    }
}
