package markup;

import java.util.List;

public class Paragraph implements Elements {
    private final List<Texts> list;

    public Paragraph(List<Texts> list) {
        this.list = list;
    }

    @Override
    public void toMarkdown(StringBuilder str) {
        for (Texts i : list) {
            i.toMarkdown(str);
        }
    }
    @Override
    public void toBBCode(StringBuilder str) {
        for (Texts i : list) {
            i.toBBCode(str);
        }
    }

}
