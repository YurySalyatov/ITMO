package expression.exceptions;

import expression.MultiExpression;

public class CheckedDivide extends Checker{

    public CheckedDivide(MultiExpression a, MultiExpression b) {
        super(a, b, "/");
    }

    protected int check(int a, int b) {
        if (a == Integer.MIN_VALUE && b == -1) {
            throw new OverFlowExeption("overflow");
        }
        else if (b == 0) {
            throw new DivadeByZeroExeption("divade by 0");
        }
        return a / b;
    }

    @Override
    protected int operation(int a, int b) {
        return check(a, b);
    }


}
