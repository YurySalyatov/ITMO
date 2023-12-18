package markup;

import java.util.List;

public class Strikeout extends AbstractClass {

    private final static String signM = "~";
    private final static String signHb = "<s>";
    private final static String signHe = "</s>";

    public Strikeout(List<InterfaceForText> list) {
        super(list, signM, signHb, signHe);
    }
}
