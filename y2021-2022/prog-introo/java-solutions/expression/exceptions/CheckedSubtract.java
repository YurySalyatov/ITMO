package expression.exceptions;

import expression.*;

public class CheckedSubtract extends Checker{

    public CheckedSubtract(MultiExpression a, MultiExpression b) {
        super(a, b, "-");
    }

    private boolean check(int a, int b) throws OverFlowExeption{
        if (a >= 0 && b < 0 && a - b <= 0) {
            return false;
        } else if (a < 0 && b > 0 && a - b >= 0) {
            return false;
        }
        return true;
    }

    @Override
    protected int operation(int a, int b) {
        if (check(a, b)) {
            return a - b;
        } else {
            throw new OverFlowExeption("overflow");
        }
    }


    

}
