package queue;

// Model: a[1]..a[n]
// Inv: n >= 0 && forall i=1..n: a[i] != null
// Let: immutable(k): forall i=1..k: a'[i] = a[i]
public interface Queue {
    // Pre: element != null
    // Post: n' = n + 1 &&
    //       a'[n'] = element &&
    //       immutable(n')
    void enqueue(Object element);

    // Pre: n > 0
    // Post: R = a[1] && n' = n - 1 && immutable(n')
    Object dequeue();

    // Pre: n > 0
    // Post: R = a[1] && n' = n && immutable(n')
    Object element();

    // Pre: true
    // Post: R = n && n' = n && immutable(n)
    int size();

    // Pre: true
    // Post: queue.isEmpty
    boolean isEmpty();

    // Pre: true
    // Post: R = (n = 0) && n' = n && immutable(n)
    void clear();

    //Pre: True
    //Post: for all a[i] : ( i: i = 1......n && not exist: (j != i): a[j] == a[i]) &&
    // && (a.index() < b.index()) -> (a'.index() < b'.index()) for all a, b in queue
    void distinct();
}
