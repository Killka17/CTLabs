package queue;


public class MyQueueTest {
    public static void main(String[] args) {
        queueModuleTest();
        ArrayQueueADT queueADT = ArrayQueueADT.create();
        queueADTTest(queueADT);
        queueTest();
    }

    private static void queueTest() {
        System.out.println("testing ArrayQueue");
        ArrayQueue queue = new ArrayQueue();
        assert queue.isEmpty();
        for (int i = 0; i < 10; i++)
            queue.enqueue(i);
        assert queue.size() == 10;
        for (int i = 0; i < 5; i++)
            queue.dequeue();
        assert queue.size() == 5;
        assert queue.element().equals(5);
        assert queue.dequeue().equals(5);
        queue.clear();
        assert queue.isEmpty();
        System.out.println("testing of the ArrayQueue class completed without errors");
    }

    private static void queueADTTest(ArrayQueueADT queueADT) {
        System.out.println("testing ArrayQueueADT");
        assert ArrayQueueADT.isEmpty(queueADT);
        for (int i = 0; i < 10; i++)
            ArrayQueueADT.enqueue(queueADT, i);
        assert ArrayQueueADT.size(queueADT) == 10;
        for (int i = 0; i < 5; i++)
            ArrayQueueADT.dequeue(queueADT);
        assert ArrayQueueADT.size(queueADT) == 5;
        assert ArrayQueueADT.element(queueADT).equals(5);
        assert ArrayQueueADT.dequeue(queueADT).equals(5);
        ArrayQueueADT.clear(queueADT);
        assert ArrayQueueADT.size(queueADT) == 0;

        System.out.println("testing of the ArrayQueueADT class completed without errors");

    }

    private static void queueModuleTest() {
        System.out.println("testing ArrayQueueModule");
        assert ArrayQueueModule.isEmpty();
        for (int i = 0; i < 10; i++)
            ArrayQueueModule.enqueue(i);
        assert ArrayQueueModule.size() == 10;
        for (int i = 0; i < 5; i++)
            ArrayQueueModule.dequeue();
        assert ArrayQueueModule.size() == 5;
        assert ArrayQueueModule.element().equals(5);
        assert ArrayQueueModule.dequeue().equals(5);
        ArrayQueueModule.clear();
        assert ArrayQueueModule.size() == 0;

        System.out.println("testing of the ArrayQueueModule class completed without errors");

    }

}
