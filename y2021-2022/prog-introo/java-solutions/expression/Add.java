package expression;

public class Add extends AbstractOp{
    private static final String OPER = "+";

    public Add(MultiExpression a, MultiExpression b) {
        super(a, b, OPER);
    }

    public int operation(int a, int b) {
        return a + b;
    }
}
