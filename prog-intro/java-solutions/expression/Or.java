package expression;

public class Or extends Operations {


    public Or(Expressions left, Expressions right) {
        super(left, right, "|");
    }

    @Override
    public int count(int a, int b) {
        return a |b;
    }

}