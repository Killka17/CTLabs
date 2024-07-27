package game;

public abstract class AbstractPlayer implements Player {
    String name = null;
    public void setName(String str) {
        name = str;
    }
    public String getName() {
        return name;
    }

}
