package queue;

// :NOTE: no tests

public class ArrayQueueModuleTest {
    public static void main(String[] args) {
//        for (int i = 0; i < 20; i++) {
//            ArrayQueueModule.enqueue("e_" + i);
//        }
//        System.out.println("1");
//        for (int i = 0; i < 13; i++) {
//            System.out.println(ArrayQueueModule.dequeue());
//        }
//        System.out.println("2");
//        for (int i = 20; i < 26; i++) {
//            System.out.println(ArrayQueueModule.element());
//            ArrayQueueModule.enqueue("e_" + i);
//        }
//        System.out.println("3");
//        // for (int i = 0; i < 30; i++) {
//        //     System.out.println(ArrayQueueModule.dequeue());
//        //     int r = ArrayQueueModule.r;
//        //     int l = ArrayQueueModule.l;
//        //     ArrayQueueModule.enqueue("e_" + (20 + i));
//        // }
//        ArrayQueueModule.clear();
//        while (!ArrayQueueModule.isEmpty()) {
//            System.out.println(ArrayQueueModule.dequeue());
//        }
//        // for (int i = 0; i < Integer.MAX_VALUE; i++) {
//        //     ArrayQueueModule.enqueue("e_" + i);
//        //     if (i % 10_000_000 == 0) {
//        //         System.out.println((double)(i / Integer.MAX_VALUE) * 100);
//        //     }
//        // }
//        ArrayQueueModule.enqueue("e_-1");
//        while (!ArrayQueueModule.isEmpty()) {
//            System.out.println(ArrayQueueModule.dequeue());
//        }
        for (int i = 0; i < 3; i++) {
            ArrayQueueModule.enqueue("value");
        }
    }
}
