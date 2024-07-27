package expression.exceptions;



import expression.*;

public class CheckedAdd extends Operations {
    public CheckedAdd(Expressions left, Expressions right) {
        super(left, right, "+");
    }

    @Override
    public int count(int a, int b) {
        checkOverflow(a, b);
        return a + b;
    }

    private void checkOverflow(int a, int b) {
        if ((a > 0 && b > 0 && a > Integer.MAX_VALUE - b) || (a < 0 && b < 0 && a < Integer.MIN_VALUE - b)) {
            throw new OverflowException("Add overflow");
        }
    }

}

