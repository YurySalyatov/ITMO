package expression;

public class LeftZeroes extends UnarOperation{

    private static final String OPER = "l0";
    
    public LeftZeroes(MultiExpression a) {
        super(a, OPER);
    }

    @Override
    protected int operation(int a) {
        if (a < 0) {
            return 0;
        } else {
            int count = 0;
            while (a > 0){
                a = a >>> 1;
                count ++;
            }
            return 32 - count;
        }
    }
    
}
