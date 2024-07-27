package markup;

import java.util.List;

public class Strikeout extends mkup {
    public Strikeout(List<Texts> list) {
        super(list, "~", "[s]", "[/s]");
    }
}
