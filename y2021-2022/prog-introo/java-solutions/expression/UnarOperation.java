package expression;

import java.util.Objects;

public abstract class UnarOperation implements MultiExpression{
    private final MultiExpression a;
    private final String oper;

    public UnarOperation(MultiExpression a, String oper) {
        this.a = a;
        this.oper = oper;
    }

    @Override
    public String toString() {
        return oper + "(" + a.toString() + ")";
    }
    @Override
    public boolean equals(Object obj) {
        if (obj == null || this.getClass() != obj.getClass()) {
            return false;
        }
        UnarOperation that = (UnarOperation) obj;
        return this.a.equals(that.a) && this.oper.equals(that.oper);
    }

    @Override
    public int hashCode() {
        return Objects.hash(a, oper);
    }
    
    protected abstract int operation(int a);
    public int evaluate(int value) {
        
        return this.operation(a.evaluate(value));
    }

    public int evaluate(int x, int y, int z) {
        return this.operation(a.evaluate(x, y, z));
    }
}
