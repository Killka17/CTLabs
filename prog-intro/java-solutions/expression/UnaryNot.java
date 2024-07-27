package expression;

public class UnaryNot extends Values{

    Expressions val;

    public UnaryNot(Expressions val) {
        super("~(" + val.toString() + ")");
        this.val = val;
    }

    @Override
    public int evaluate(int x) {
        return ~val.evaluate(x);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return ~val.evaluate(x, y, z);
    }
}
