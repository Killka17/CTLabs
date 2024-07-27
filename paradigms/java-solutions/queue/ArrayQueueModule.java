package queue;

import java.util.Arrays;
import java.util.function.Predicate;

// Model: a[1]..a[n]
// Inv: n >= 0 && forall i=1..n: a[i] != null
// Let: immutable(k): forall i=1..k: a'[i] = a[i]
public class ArrayQueueModule {
    private static int front = 0;
    private static int back = -1;
    private static int size = 0;

    private static Object[] elements = new Object[5];

    // Pre: element != null
    // Post: n' = n + 1 &&
    //       a'[n'] = element &&
    //       immutable(n)

    public static void enqueue(Object element) {
        assert element != null;

        ensureCapacity(++back);

        size++;
        elements[back] = element;
    }
    // Pre: n > 0
    // Post: R = a[0] && n' = n - 1 && immutable(n')
    public static Object dequeue() {
        assert !isEmpty();

        size--;
        return elements[front++];
    }
    // Pre: n > 0
    // Post: R = a[0] && n' = n - 1 && immutable(n')
    public static Object element() {
        return elements[front];
    }
    // Pre: true
    // Post: R = n && n' = n && immutable(n)
    public static int size() {
        return size;
    }
    // Pre: true
    // Post: R = (n = 0) && n' = n && immutable(n)
    public static boolean isEmpty() {
        return size == 0;
    }

    private static void ensureCapacity(int last) {
        if (elements.length <= last) {
            Object[] newElements = new Object[elements.length * 2];
            for (int i = 0; i < elements.length; i++) {
                newElements[i] = elements[(front + i) % elements.length];
            }
            elements = newElements;
            front = 0;
            back = size;
        }
    }
    // Pre: true
    // Post: R = (n = 0) && n' = n && immutable(n)
    public static void clear() {
        Arrays.fill(elements, null);
        front = 0;
        back = -1;
        size = 0;
    }

    public static int indexIf(Predicate<Object> pred) {
        return findIndexWithPredicate(pred, false);
    }

    // Pre: True
    // Post: r = max i: Predicate(queue[i]) == True
    public static int lastIndexIf(Predicate<Object> pred) {
        return findIndexWithPredicate(pred, true);
    }

    private static int findIndexWithPredicate(Predicate<Object> pred, boolean findLast) {
        int resultIndex = findLast ? -1 : size;
        for (int i = 0; i < size; i++) {
            int currentIndex = findLast ? size - 1 - i : i;
            if (pred.test(elements[(currentIndex + front) % elements.length])) {
                resultIndex = currentIndex;
                break;
            }
        }
        return resultIndex >= 0 && resultIndex < size ? resultIndex : -1;
    }

}
