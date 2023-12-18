package expression;

public class Divide extends AbstractOp{
    private static final String OPER = "/";

    public Divide(MultiExpression a, MultiExpression b) {
        super(a, b, OPER);
    }

    public int operation(int a, int b) {
        return a / b;
    }
}
