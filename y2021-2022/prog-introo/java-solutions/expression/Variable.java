package expression;

import java.util.Objects;

public class  Variable implements MultiExpression{
    
    private final String name;

    public Variable(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return this.name;
    }
    @Override
    public boolean equals(Object obj) {
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        if (this == obj) {
            return true;
        }
        Variable variable = (Variable) obj;
        return name.equals(variable.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name);
    }
    public int evaluate (int value) {
        if (name.length() > 1) {
            return -value;
        }
        return value;

    }
    public int evaluate (int x, int y, int z) {
        if (name.length() < 2) {
            if (name.equals("x")) {
                return x;
            }
            if (name.equals("y")) {
                return y;
            }
            return z;
        }
        if (name.equals("-x")) {
            return -x;
        }
        if (name.equals("-y")) {
            return -y;
        }
        return -z;
    }
}
