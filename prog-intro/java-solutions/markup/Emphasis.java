package markup;

import java.util.List;

public class Emphasis extends mkup {

    public Emphasis(List<Texts> list) {
        super(list, "*", "[i]", "[/i]");
    }
}

