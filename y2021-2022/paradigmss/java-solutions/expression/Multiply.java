package expression;

public class Multiply extends AbstractOp{
    private static final String OPER = "*";

    public Multiply(MultiExpression a, MultiExpression b) {
        super(a, b, OPER);
    }
    
    public int operation(int a, int b) {
        return a * b;
    }
}
