package expression.exceptions;

import expression.*;

public class ExpressionParser implements Parser {

    private String string;
    private char ch;
    private int pos;
    private static final char END = 0;

    public ExpressionParser() {
        this.string = "";

    }

    public MultiExpression parse(String string) {
        this.string = string;
        pos = 0;
        take();
        skipWhitespace();
        MultiExpression first = parseNext();
        skipWhitespace();
        while (!end()) {
            first = constract(first);
            skipWhitespace();
        }
        return first;

    }

    private MultiExpression constract(MultiExpression first) {
        String oper = nextOper();
        skipWhitespace();
        switch (oper) {
            case "+":
                return new CheckedAdd(first, nextElforAddandSub());
            case "-":
                return new CheckedSubtract(first, nextElforAddandSub());
            case "*":
                return new CheckedMultiply(first, nextForMultiAndDivade());
            case "/":
                return new CheckedDivide(first, nextForMultiAndDivade());
            case "min":
                return new Min(first, nextForMinMax());
            case "max":
                return new Max(first, nextForMinMax());

            default:
                throw new OperationException("Expected +, -, *, /, min, max, found: " + oper);
        }
    }

    private MultiExpression parseNext() {
        skipWhitespace();
        if (take('-')) {
            return parsewithUnarMinus();
        } else if (take('t')) {
            if (take('0')) {
                if (Character.isWhitespace(ch) || ch == '-' || ch == '(') {
                    return new RightZeroes(parseNext());
                } else {
                    throw new NextSymbolExeption("Expected whitespace, unar minus or (, found: " + take());
                }
            } else {
                throw new NextSymbolExeption("Expeceted 0 after t, found: " + take());
            }
        } else if (take('l')) {
            if (take('0')) {
                if (Character.isWhitespace(ch) || ch == '-' || ch == '(') {
                    return new LeftZeroes(parseNext());
                } else {
                    throw new NextSymbolExeption("Expected whitespace, unar minus or (, found: " + take());
                }
            } else {
                throw new NextSymbolExeption("Expeceted 0 after l, found: " + take());
            }
        } else if (take('(')) {
            return parseElement();
        } else if (ch == 'x' || ch == 'y' || ch == 'z') {
            return parseVariable();
        } else if (isAdiget()) {
            return parseConst(1);
        } else {
            throw new NextExpressionException("Expexted expression, found: " + take());
        }
    }

    private MultiExpression parseElement() {
        int openscob = 1;
        skipWhitespace();
        while (take('(')) {
            openscob++;
            skipWhitespace();
        }
        MultiExpression first = parseNext();
        skipWhitespace();
        while (openscob != 0) {
            if (take(')')) {
                openscob--;
                skipWhitespace();
            } else {
                first = constract(first);
                skipWhitespace();
            }
        }
        return first;
    }

    private MultiExpression nextForMultiAndDivade() {
        MultiExpression first = parseNext();
        skipWhitespace();
        return first;
    }

    private MultiExpression nextElforAddandSub() {
        MultiExpression first = parseNext();
        skipWhitespace();
        while (ch == '*' || ch == '/') {
            first = constract(first);
            skipWhitespace();
        }
        return first;
    }

    private MultiExpression nextForMinMax() {
        MultiExpression first = parseNext();
        skipWhitespace();
        while (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            first = constract(first);
            skipWhitespace();
        }
        return first;
    }

    private MultiExpression parsewithUnarMinus() {
        skipWhitespace();
        if (ch == 'x' || ch == 'y' || ch == 'z') {
            return new CheckedNegate(parseVariable());
        } else if (isAdiget()) {
            return parseConst(-1);
        }
        return new CheckedNegate(parseNext());
    }

    private MultiExpression parseVariable() {
        if (ch == 'x' || ch == 'y' || ch == 'z') {
            return new Variable(Character.toString(take()));
        } else {
            throw new VariableExeption("Expected x, y, z, find: " + take());
        }
    }

    private MultiExpression parseConst(int sign) {
        int val = 0;
        while (isAdiget()) {
            val = val * 10 + (take() - '0') * sign;
            if (!(sign < 0 && val <= 0) && !(sign > 0 && val >= 0)) {
                throw new IntegerOverflowException(
                        "this number more than " + Integer.MAX_VALUE + " or less than " + Integer.MIN_VALUE);
            }
        }
        return new Const(val);
    }

    private boolean isAdiget() {
        return '0' <= ch && ch <= '9';
    }

    private void skipWhitespace() {
        while (Character.isWhitespace(ch)) {
            take();
        }
    }

    private String nextOper() {
        if (ch != 'm') {
            return Character.toString(take());
        } else {
            String oper = Character.toString(take()) + Character.toString(take()) + Character.toString(take());
            if (Character.isWhitespace(ch) || ch == '(' || ch == '-') {
                return oper;
            } else {
                throw new NextSymbolExeption("Expexted whitespace, minys or (, find: " + take());
            }
        }
    }

    private boolean end() {
        return ch == END;
    }

    private boolean take(char expect) {
        if (ch == expect) {
            take();
            return true;
        }
        return false;
    }

    private char take() {
        char res = this.ch;
        if (hasNext()) {
            this.ch = next();
        } else {
            ch = END;
        }
        return res;
    }

    private boolean hasNext() {
        return pos < string.length();
    }

    private char next() {
        return string.charAt(pos++);
    }

}
