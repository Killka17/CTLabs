package queue;

import java.util.LinkedHashSet;
import java.util.Set;

public abstract class AbstractQueue implements Queue {

    protected int size = 0;


    public void enqueue(Object element) {
        assert element != null;
        enqueueImpl(element);
        size++;
    }


    public Object dequeue() {
        assert !isEmpty();
        size--;
        return dequeueImpl();
    }


    public Object element() {
        assert size > 0;
        return elementImpl();
    }


    public int size() {
        return size;
    }


    public void clear() {
        size = 0;
        clearImpl();
    }


    public boolean isEmpty() {
        return size == 0;
    }

    public void distinct() {

        Set<Object> uniqueValues = new LinkedHashSet<>();
        int counter = size;
        for (int i = 0; i < counter; i++) {
            uniqueValues.add(dequeue());
        }
        for (Object i : uniqueValues) {
            enqueue(i);
        }
    }

    protected abstract void clearImpl();

    protected abstract Object elementImpl();

    protected abstract Object dequeueImpl();

    protected abstract void enqueueImpl(Object element);
}
