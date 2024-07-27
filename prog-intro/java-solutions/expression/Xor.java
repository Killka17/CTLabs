package expression;

public class Xor extends Operations {


    public Xor(Expressions left, Expressions right) {
        super(left, right, "^");
    }

    @Override
    public int count(int a, int b) {
        return a ^ b;
    }
}