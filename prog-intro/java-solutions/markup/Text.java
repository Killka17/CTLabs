package markup;

public class Text extends Texts {
    private final String string;
    public Text (String string) {
        this.string = string;
    }

    @Override
    public void toMarkdown(StringBuilder str) {
        str.append(string);
    }
    @Override
    public void toBBCode(StringBuilder str) {
        str.append(string);
    }
}
