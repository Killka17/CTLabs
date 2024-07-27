package expression;

public class And extends Operations {


    public And(Expressions left, Expressions right) {
        super(left, right, "&");
    }

    @Override
    public int count(int a, int b) {
        return a & b;
    }

}
