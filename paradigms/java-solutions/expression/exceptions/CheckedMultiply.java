package expression.exceptions;


import expression.Expressions;
import expression.Operations;

public class CheckedMultiply extends Operations {
    public CheckedMultiply(Expressions left, Expressions right) {
        super(left, right, "*");
    }

    @Override
    public int count(int a, int b) {
        checkOverflow(a, b);
        return a * b;
    }

    private void checkOverflow(int a, int b) {
        if (a != 0 && b != 0 && (a * b / a != b || a * b / b != a)) {
            throw new OverflowException("Multiply overflow");
        }
    }
}
