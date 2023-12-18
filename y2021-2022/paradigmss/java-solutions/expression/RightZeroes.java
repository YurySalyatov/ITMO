package expression;

public class RightZeroes extends UnarOperation{

    private final static String OPER = "t0";

    public RightZeroes(MultiExpression a) {
        super(a, OPER);
    }

    @Override
    protected int operation(int a) {
        int count = 0;
        if (a == 0) {
            return 32;
        }
        while (a % 2 == 0) {
            count ++;
            a = a >>> 1;
        }
        return count;
    }
    
}
