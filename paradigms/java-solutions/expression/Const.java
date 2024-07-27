package expression;

import java.util.List;

public class Const extends Values {

    int val;

    public Const(int val) {
        super(Integer.toString(val));

        this.val = val;
    }



    public int evaluate() {
        return val;
    }

    @Override
    public int evaluate(int x) {
        return val;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return val;
    }

    @Override
    public boolean equals(Object object) {
        if (object == null || getClass() != object.getClass()) {
            return false;
        }
        Const con = (Const) object;
        return val == con.val;
    }

    @Override
    public int evaluate(List<Integer> variables) {
        return val;
    }
}
