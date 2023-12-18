package expression;

import java.util.Objects;

public abstract class AbstractOp implements MultiExpression{
    private MultiExpression a;
    private MultiExpression b;
    private final String OPER;

    public AbstractOp (MultiExpression a, MultiExpression b, String oper) {
        this.a = a;
        this.b = b;
        this.OPER = oper;
    }

    @Override
    public String toString() {
        return "(" + a.toString() + " " + OPER + " " + b.toString() + ")";
    }
    @Override
    public boolean equals(Object obj) {
        if (obj == null || this.getClass() != obj.getClass()) {
            return false;
        }
        
        AbstractOp that = (AbstractOp) obj;
        return this.a.equals(that.a) && this.b.equals(that.b) && this.OPER.equals(that.OPER);
    }

    @Override
    public int hashCode() {
        return Objects.hash(a, b, OPER);
    }
    
    protected abstract int operation(int a, int b);
    
    public int evaluate(int value) {
        return this.operation(a.evaluate(value), b.evaluate(value));
    }

    public int evaluate(int x, int y, int z) {
        return this.operation(a.evaluate(x, y, z), b.evaluate(x, y, z));
    }
}
