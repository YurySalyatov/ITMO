package expression.exceptions;

import expression.MultiExpression;
import java.util.Objects;

public abstract class Checker implements MultiExpression{
    private final MultiExpression a;
    private final MultiExpression b;
    private final String oper;
    
    public Checker(MultiExpression a, MultiExpression b, String oper) {
        this.a = a;
        this.b = b;
        this.oper = oper;
    }
    
    protected abstract int operation(int a, int b) throws OverFlowExeption;
    @Override
    public String toString() {
        return "(" + a.toString() + " " + oper + " " + b.toString() + ")";
    }
    @Override
    public boolean equals(Object obj) {
        if (obj == null || this.getClass() != obj.getClass()) {
            return false;
        }
        Checker that = (Checker) obj;
        return this.a.equals(that.a) && this.b.equals(that.b) && this.oper.equals(that.oper);
    }

    @Override
    public int hashCode() {
        return Objects.hash(a, b, oper);
    }
    
    public int evaluate(int value) {
        return this.operation(a.evaluate(value), b.evaluate(value));
    }

    public int evaluate(int x, int y, int z) {
        return this.operation(a.evaluate(x, y, z), b.evaluate(x, y, z));
    }
}
