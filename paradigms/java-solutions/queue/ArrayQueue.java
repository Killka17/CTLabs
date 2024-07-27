package queue;

import java.util.Arrays;
import java.util.function.Predicate;


public class ArrayQueue extends AbstractQueue {
    private int front = 0;
    private int back = -1;

    private Object[] elements = new Object[5];


    @Override
    protected Object dequeueImpl() {
        return elements[front++];
    }

    protected void enqueueImpl(Object element) {
        ensureCapacity(++back);
        elements[back] = element;
    }


    public Object elementImpl() {
        return elements[front];
    }


    private void ensureCapacity(int last) {
        if (elements.length <= last) {
            Object[] newElements = new Object[elements.length * 2];
            System.arraycopy(elements, front, newElements, 0, elements.length - front);
            System.arraycopy(elements, 0, newElements, elements.length - front, back);
            elements = newElements;
            front = 0;
            back = size;
        }
    }

    public void clearImpl() {
        Arrays.fill(elements, null);
        front = 0;
        back = -1;
    }

    //Pre: True
    //Post: r = min i: Predicate(queue[i]) == True
    public int indexIf(Predicate<Object> pred) {
        return findIndexWithPredicate(pred, false);
    }

    // Pre: True
    // Post: r = max i: Predicate(queue[i]) == True
    public int lastIndexIf(Predicate<Object> pred) {
        return findIndexWithPredicate(pred, true);
    }

    private int findIndexWithPredicate(Predicate<Object> pred, boolean findLast) {
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
