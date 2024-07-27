package expression;

public class Add extends Operations {


    public Add(Expressions left, Expressions right) {
        super(left, right, "+");
    }

    @Override
    public int count(int a, int b) {
        return a + b;
    }

}
