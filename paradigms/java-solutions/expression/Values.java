package expression;

import java.util.Objects;

public abstract class Values implements Expressions {

    private final String val;

    public Values(String val) {
        this.val = val;
    }

    @Override
    public String toString() {
        return val;
    }

    @Override
    public int hashCode() {
        return Objects.hash(val) * 1337_228;
    }

}
