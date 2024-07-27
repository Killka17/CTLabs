package expression.exceptions;

import expression.Expressions;
import expression.Values;

public class CheckedNegate extends Values {

    private final Expressions vy;
    public CheckedNegate(Expressions vy) {
        super("-(" + vy + ")");
        this.vy = vy;
    }

    @Override
    public int evaluate(int x) {
        checkOverflow(vy.evaluate(x));
        return vy.evaluate(x) * -1;
    }

    private void checkOverflow(int evaluate) {
        if (evaluate == Integer.MIN_VALUE) {
            throw new OverflowException("Negative Overflow");
        }
    }

    @Override
    public int evaluate(int x, int y, int z) {
        checkOverflow(vy.evaluate(x, y, z));
        return vy.evaluate(x, y, z) * -1;
    }
}
