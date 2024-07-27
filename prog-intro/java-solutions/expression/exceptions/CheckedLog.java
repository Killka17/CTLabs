package expression.exceptions;

import expression.Expressions;
import expression.Values;


public class CheckedLog extends Values {

    Expressions val;

    public CheckedLog(Expressions val) {
        super("log2(" + val.toString() + ")");
        this.val = val;
    }

    @Override
    public int evaluate(int x) {
        return calculateLog(val.evaluate(x));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return calculateLog(val.evaluate(x, y, z));
    }


    public int calculateLog(int x) {
        if (x <= 0) {
            throw new LogExcepsion();
        } else {
            return Integer.toBinaryString(x).length() - 1;
        }
    }
}