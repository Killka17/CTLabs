package expression.exceptions;

import expression.Expressions;
import expression.Operations;

public class CheckedDivide extends Operations {
    public CheckedDivide(Expressions left, Expressions right) {
        super(left, right, "/");
    }

    @Override
    public int count(int a, int b) {
        checkOverflow(a, b);
        checkDivisionByZero(b);
        return a / b;
    }

    private void checkOverflow(int a, int b) {
        if (a == Integer.MIN_VALUE && b == -1) {
            throw new OverflowException("Divide overflow");
        }
    }
    private void checkDivisionByZero(int b) {
        if (b == 0) {
            throw new DivisionByZeroException();
        }
    }

}
