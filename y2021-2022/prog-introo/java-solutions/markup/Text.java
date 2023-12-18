package markup;

public class Text implements InterfaceForText{
    private StringBuilder sb;

    public Text (String str) {
        this.sb = new StringBuilder(str);
    }

    public void toMarkdown(StringBuilder sb) {
        sb.append(this.sb);
    }

    public void toHtml (StringBuilder sb) {
        sb.append(this.sb);
    }
}
