package expression.exceptions;

import expression.MultiExpression;

public class CheckedMultiply extends Checker{

    public CheckedMultiply(MultiExpression a, MultiExpression b) {
        super(a, b, "*");
    }



    protected boolean check(int a, int b) {
        if (a != 0 && b != 0) {
            if (a * b / b != a || a * b / a != b) {
                return false;
            }
        }
        return true;
    }

    @Override
    protected int operation(int a, int b) {
        if (check(a, b)) {
            return a * b;
        } else {
            throw new OverFlowExeption("overflow");
        }
    }

    
    

}
