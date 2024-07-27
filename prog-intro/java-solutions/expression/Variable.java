package expression;

import java.util.Objects;

public class Variable extends Values {

    String val;

    public Variable(String val) {
        super(val);
        this.val = val;

    }

    @Override
    public int evaluate(int x) {
        return x;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        if (Objects.equals(val, "x")) return x;
        else if (Objects.equals(val, "y")) return y;
        else return z;
    }


    @Override
    public boolean equals(Object object) {
        if (object == null || object.getClass() != getClass()) {
            return false;
        }
        Variable var = (Variable) object;
        return Objects.equals(val, var.val);
    }
}