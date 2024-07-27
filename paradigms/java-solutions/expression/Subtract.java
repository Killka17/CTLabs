package expression;

public class Subtract extends Operations {
    public Subtract(Expressions left, Expressions right) {
        super(left, right, "-");
    }

    @Override
    public int count(int a, int b) {
        return a - b;
    }
}
