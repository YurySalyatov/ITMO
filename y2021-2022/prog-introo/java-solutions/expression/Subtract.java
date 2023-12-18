package expression;

public class Subtract extends AbstractOp{
    private static final String OPER = "-";

    public Subtract(MultiExpression a, MultiExpression b) {
        super(a, b, OPER);
    }

    public int operation(int a, int b) {
        return a - b;
    }

}
