package expression;

public class UnaryMines extends Values{

    Expressions val;

    public UnaryMines(Expressions val) {
        super("-(" + val.toString() + ")");
        this.val = val;
    }

    public static Expressions createUnaryMines(Expressions expressions) {
        if (expressions instanceof Const) {
            return new Const(-((Const) expressions).evaluate());
        }
        return new UnaryMines(expressions);
    }




    @Override
    public int evaluate(int x) {
        return -val.evaluate(x);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return -val.evaluate(x, y, z);
    }
}
