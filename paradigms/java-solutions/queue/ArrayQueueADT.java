package queue;

import java.util.Arrays;
import java.util.function.Predicate;

// Model: a[1]..a[n]
// Inv: n >= 0 && forall i=1..n: a[i] != null
// Let: immutable(k): forall i=1..k: a'[i] = a[i]
public class ArrayQueueADT {
    private int front = 0;
    private int back = -1;
    private int size = 0;

    private Object[] elements = new Object[5];

    // Pre: element != null
    // Post: n' = n + 1 &&
    //       a'[n'] = element &&
    //       immutable(n)

    public static void enqueue(ArrayQueueADT queue, Object element) {
        assert element != null;

        ensureCapacity(queue, ++queue.back);
        queue.size++;
        queue.elements[queue.back] = element;
    }
    // Pre: n > 0
    // Post: R = a[0] && n' = n - 1 && immutable(n')
    public static Object dequeue(ArrayQueueADT queue) {
        assert !isEmpty(queue);

        queue.size--;
        return queue.elements[queue.front++];
    }
    // Pre: n > 0
    // Post: R = a[0] && n' = n && immutable(n)
    public static Object element(ArrayQueueADT queue) {
        return queue.elements[queue.front];
    }
    // Pre: true
    // Post: R = n && n' = n && immutable(n)
    public static int size(ArrayQueueADT queue) {
        return queue.size;
    }
    // Pre: true
    // Post: R = (n = 0) && n' = n && immutable(n)
    public static boolean isEmpty(ArrayQueueADT queue) {
        return queue.size == 0;
    }

    private static void ensureCapacity(ArrayQueueADT queue, int last) {
        if (queue.elements.length <= last) {
            Object[] newElements = new Object[queue.elements.length * 2];
            for (int i = 0; i < queue.elements.length; i++) {
                newElements[i] = queue.elements[(queue.front + i) % queue.elements.length];
            }
            queue.elements = newElements;
            queue.front = 0;
            queue.back = queue.size;
        }
    }
    // Pre: true
    // Post: R = (n = 0) && n' = n && immutable(n)
    public static void clear(ArrayQueueADT queue) {
        Arrays.fill(queue.elements, null);
        queue.front = 0;
        queue.back = -1;
        queue.size = 0;
    }

    public static ArrayQueueADT create() {
        ArrayQueueADT queueADT = new ArrayQueueADT();
        queueADT.elements = new Object[10];
        return queueADT;
    }

    public static int indexIf(ArrayQueueADT q, Predicate<Object> pred) {
        return findIndexWithPredicate(q, pred, false);
    }

    // Pre: True
    // Post: r = max i: Predicate(queue[i]) == True
    public static int lastIndexIf(ArrayQueueADT q, Predicate<Object> pred) {
        return findIndexWithPredicate(q, pred, true);
    }

    private static int findIndexWithPredicate(ArrayQueueADT q, Predicate<Object> pred, boolean findLast) {
        int resultIndex = findLast ? -1 : q.size;
        for (int i = 0; i < q.size; i++) {
            int currentIndex = findLast ? q.size - 1 - i : i;
            if (pred.test(q.elements[(currentIndex + q.front) % q.elements.length])) {
                resultIndex = currentIndex;
                break;
            }
        }
        return resultIndex >= 0 && resultIndex < q.size ? resultIndex : -1;
    }



}
