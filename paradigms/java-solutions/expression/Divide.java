package expression;

public class Divide extends Operations {
    public Divide(Expressions left, Expressions right) {
        super(left, right, "/");
    }

    @Override
    public int count(int a, int b) {
        return a / b;
    }
}
