package queue;

import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

public class LinkedQueue extends AbstractQueue {
    private Node front = null;
    private Node back = null;


    private static class Node {
        private final Object value;
        private Node next;

        public Node(Object value, Node next) {
            assert value != null;

            this.value = value;
            this.next = next;
        }
    }

    @Override
    protected Object dequeueImpl() {
        Object res = front.value;
        front = front.next;
        return res;
    }

    protected void enqueueImpl(Object element) {
        if (size == 0) {
            back = new Node(element, null);
            front = back;
        } else if (size == 1) {
            back = new Node(element, front);
            front.next = back;
        } else {
            Node buff = new Node(element, front);
            back.next = buff;
            back = buff;
        }
    }

    public Object elementImpl() {
        return front.value;
    }

    public void clearImpl() {
        front = null;
        back = null;
    }
}
