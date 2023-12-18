package expression.exceptions;

import java.util.Objects;

import expression.MultiExpression;

public class CheckedNegate implements MultiExpression{

    private final MultiExpression b;

    public CheckedNegate( MultiExpression b) {
        this.b = b;
    }

    protected boolean check(int b) {
        if (b == Integer.MIN_VALUE) {
            return true;
        }
        return false;
    }

    @Override
    public int evaluate(int x) {
        if(check(b.evaluate(x))) {
            return -b.evaluate(x);
        } else {
            throw new OverFlowExeption("owerflow");
        }
    }

    @Override
    public int evaluate(int x, int y, int z) {
        if(check(b.evaluate(x, y, z))) {
            throw new OverFlowExeption("owerflow");
        } else {
            return -b.evaluate(x, y, z);
        }
    }

    @Override
    public String toString() {
        return "-(" + b.toString() + ")";
    }
    @Override
    public boolean equals(Object obj) {
        if (obj == null || this.getClass() != obj.getClass()) {
            return false;
        }
        CheckedNegate that = (CheckedNegate) obj;
        return this.b.equals(that.b);
    }

    @Override
    public int hashCode() {
        return Objects.hash(b, "-");
    }
    


}
