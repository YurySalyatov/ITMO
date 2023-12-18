package expression;

public class UnarMinus extends UnarOperation{

    public final static String OPER = "-";
    
    public UnarMinus(MultiExpression a) {
        super(a, OPER);
    }

    @Override
    protected int operation(int a) {
        return -1 * a;
    }
}
