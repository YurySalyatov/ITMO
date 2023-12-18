package expression;


public class Max extends AbstractOp {
;
    private static final String OPER = "max";

    public Max(MultiExpression a, MultiExpression b) {
        super(a, b, OPER);
    }

    public int operation(int a, int b) {
        return Math.max(a,b);
    }
}
