package expression;

import java.util.List;
import java.util.Objects;

public abstract class Operations implements Expressions {


    private final Expressions left;
    private final Expressions right;
    private final String sign;


    public Operations(Expressions left, Expressions right, String sign) {
        this.left = left;
        this.right = right;
        this.sign = sign;

    }

    @Override
    public int evaluate(int x) {
        return count(left.evaluate(x), right.evaluate(x));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return count(left.evaluate(x, y, z), right.evaluate(x, y, z));
    }

    @Override
    public int evaluate(List<Integer> variables) {
        return count(left.evaluate(variables), right.evaluate(variables));
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " " + sign + " " + right.toString() + ")";
    }

    @Override
    public boolean equals(Object object) {
        if (object == null || object.getClass() != getClass()) {
            return false;
        }
        Operations op = (Operations) object;
        return left.equals(op.left) && right.equals(op.right);
    }

    @Override
    public int hashCode() {
        return Objects.hash(left, right, getClass()) * 1337_228;
    }

    protected abstract int count(int a, int b);


}
