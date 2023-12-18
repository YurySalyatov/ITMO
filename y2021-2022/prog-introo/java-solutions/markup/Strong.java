package markup;

import java.util.List;

public class Strong extends AbstractClass{
    private final static String signM = "__";
    private final static String signHb = "<strong>";
    private final static String signHe = "</strong>";

    public Strong(List<InterfaceForText> list) {
        super(list, signM, signHb, signHe);
    }
}
