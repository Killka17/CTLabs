package expression;

import java.util.List;

public class UnaryMinus extends Values{

    Expressions val;

    public UnaryMinus(Expressions val) {
        super("-(" + val.toString() + ")");
        this.val = val;
    }

    @Override
    public int evaluate(int x) {
        return -val.evaluate(x);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return -val.evaluate(x, y, z);
    }

    @Override
    public int evaluate(List<Integer> variables) {
        return -val.evaluate(variables);
    }
}
