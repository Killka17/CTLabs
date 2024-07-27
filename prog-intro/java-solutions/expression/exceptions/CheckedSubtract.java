package expression.exceptions;


import expression.Expressions;
import expression.Operations;

public class CheckedSubtract extends Operations {
    public CheckedSubtract(Expressions left, Expressions right) {
        super(left, right, "-");
    }

    @Override
    public int count(int a, int b) {
        checkOverflow(a, b);
        return a - b;
    }

    private void checkOverflow(int a, int b) {
        if ((b > 0 && a < 0 && a < Integer.MIN_VALUE + b) || (b < 0 && a>= 0 && a > Integer.MAX_VALUE + b)) {
            throw new OverflowException("Substract overflow");
        }
    }
}
