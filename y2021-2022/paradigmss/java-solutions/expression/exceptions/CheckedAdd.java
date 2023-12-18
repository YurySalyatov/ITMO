package expression.exceptions;

import expression.*;

public class CheckedAdd extends Checker{

    public CheckedAdd(MultiExpression a, MultiExpression b) {
        super(a, b, "+");
    }


    protected boolean check(int a, int b) {
        if (a > 0 && b > 0 && a + b <= 0) {
            return false;
        } else if (a < 0 && b < 0 && a + b >= 0) {
            return false;
        }
        return true;
    }


    @Override
    protected int operation(int a, int b) {
        if (check(a, b)) {
            return a + b;
        } else {
            throw new OverFlowExeption("overflow");
        }
    }




}
