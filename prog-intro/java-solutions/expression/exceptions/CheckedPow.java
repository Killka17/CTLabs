package expression.exceptions;

import expression.Expressions;
import expression.Values;

public class CheckedPow extends Values {
    Expressions val;

    public CheckedPow(Expressions val) {
        super("pow2(" + val.toString() + ")");
        this.val = val;
    }

    @Override
    public int evaluate(int x) {
        return calculatePow(val.evaluate(x));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return calculatePow(val.evaluate(x, y, z));
    }


    public int calculatePow(int x) {
        if (x > 30) {
            throw new OverflowException("Pow overflow");
        } else if (x < 0) {
            throw new PowExcesion();
        }
        else {
            return 1<<x;
        }
    }
}

