package expression;

import java.util.Objects;

public class Const implements MultiExpression{

    private final int c;

    public Const(int value) {
        this.c = value;
    }

    @Override
    public String toString() {
        return (Integer.toString(this.c));
    }
    @Override
    public boolean equals(Object obj) {
        if (obj == null || this.getClass() != obj.getClass()){
            return false;
        }
        Const value = (Const) obj;
        return c == value.c;
    }

    @Override
    public int hashCode() {
        return Objects.hash(c);
    }

    public int evaluate(int var) {
        return this.c;
    }
    public int evaluate (int x, int y, int z) {
        return this.c;
    }
}