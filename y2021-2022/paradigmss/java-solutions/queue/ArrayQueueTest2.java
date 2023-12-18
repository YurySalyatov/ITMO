package queue;

// :NOTE: no checks in tests

public class ArrayQueueTest2 {
    public static void main(String[] args) {
        ArrayQueue queue = new ArrayQueue();
        queue.enqueue("1");
        queue.enqueue("3");
        queue.enqueue("1");
        queue.enqueue("[a]");
        System.out.println(queue.dequeue() + " print");
        System.out.println(queue.element() + " print");
        System.out.println(queue.element() + " print");
        queue.enqueue("[b]");
        System.out.println(queue.dequeue() + " print");
        System.out.println(queue.element() + " print");


//         for (int i = 0; i < 20; i++) {
//             queue.enqueue("e_" + i);
//         }
//         System.out.println("1");
//         for (int i = 0; i < 13; i++) {
//             System.out.println(queue.dequeue());
//         }
//         System.out.println("2");
//         for (int i = 20; i < 26; i++) {
//             System.out.println(queue.element());
//             queue.enqueue("e_" + i);
//         }
//         System.out.println("3");
//         // for (int i = 0; i < 30; i++) {
//         //     System.out.println(queue.dequeue());
//         //     int r = queue.r;
//         //     int l = queue.l;
//         //     queue.enqueue("e_" + (20 + i));
//         // }
//         queue.clear();
//         while (!queue.isEmpty()) {
//             System.out.println(queue.dequeue());
//         }
//         // for (int i = 0; i < Integer.MAX_VALUE; i++) {
//         //     queue.enqueue("e_" + i);
//         //     if (i % 10_000_000 == 0) {
//         //         System.out.println((double)(i / Integer.MAX_VALUE) * 100);
//         //     }
//         // }
//         queue.enqueue("e_-1");
//         while (!queue.isEmpty()) {
//             System.out.println(queue.dequeue());
//         }
    }
}
