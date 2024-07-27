package expression;

public class Multiply extends Operations {
    public Multiply(Expressions left, Expressions right) {
        super(left, right, "*");
    }

    @Override
    public int count(int a, int b) {
        return a * b;
    }
}
