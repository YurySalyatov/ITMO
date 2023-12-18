package markup;

import java.util.List;

public class Emphasis extends AbstractClass {
    private final static String signM = "*";
    private final static String signHb = "<em>";
    private final static String signHe = "</em>";

    public Emphasis(List<InterfaceForText> list) {
        super(list, signM, signHb, signHe);
    }
}
