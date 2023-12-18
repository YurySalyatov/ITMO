package expression;


public class Min extends AbstractOp {

    private static final String OPER = "min"; 

    public Min(MultiExpression a, MultiExpression b) {
        super(a, b, OPER);
    }

    public int operation(int a, int b) {
        return Math.min(a, b);
    }
}