package markup;

import java.util.List;

public class mkup extends Texts{

    protected List<Texts> list;
    protected String mk;
    protected String bb_end;
    protected String bb_begin;


    public mkup(List<Texts> list, String mk, String bb_begin, String bb_end) {
        this.list = list;
        this.mk = mk;
        this.bb_end = bb_end;
        this.bb_begin = bb_begin;
    }

    @Override
    public void toMarkdown(StringBuilder str) {
        str.append(mk);
        for (Texts i : list) {
            i.toMarkdown(str);
        }
        str.append(mk);
    }
    @Override
    public void toBBCode(StringBuilder str) {
        str.append(bb_begin);
        for (Texts i : list) {
            i.toBBCode(str);
        }
        str.append(bb_end);
    }
}
