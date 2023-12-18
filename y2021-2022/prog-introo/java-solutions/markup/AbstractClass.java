package markup;

import java.util.List;

public class AbstractClass implements InterfaceForText{
    
    public List<InterfaceForText> list;
    public final String signM;
    public final String signHb;
    public final String signHe;

    public AbstractClass (List<InterfaceForText> interList, String signM, String signHb, String signHe) {
        this.list = interList;
        this.signM = signM;
        this.signHb = signHb;
        this.signHe = signHe;
    }

    public AbstractClass (List<InterfaceForText> interList) {
        this.list = interList;
        this.signM = "";
        this.signHb = "";
        this.signHe = "";
    }

    public void toMarkdown (StringBuilder sb) {
        sb.append(signM);
        for (InterfaceForText abs : this.list) {
            abs.toMarkdown(sb);
        }
        sb.append(signM);
    }

    public void toHtml (StringBuilder sb) {
        sb.append(signHb);
        for (InterfaceForText abs : this.list) {
            abs.toHtml(sb);
        }
        sb.append(signHe);
    }
}
