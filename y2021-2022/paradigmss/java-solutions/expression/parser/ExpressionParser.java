package expression.parser;

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
        //System.err.println(string);
        pos = 0;
        take();
        skipAllWaiteSpace();
        MultiExpression first = parseNext();
        //System.err.println(first);
        while (!end()) {
            first = constract(first);
        }
        //System.err.println(first);
        return first;
    }
    private MultiExpression constract(MultiExpression first) {
        String oper = nextOper();
        switch (oper) {
            case "+":
                return new Add(first, nextElforAddandSub());                
            case "-":
                return new Subtract(first, nextElforAddandSub());
            case "*":
                return new Multiply(first, nextForMultiAndDivade());            
            case "/":
                return new Divide(first, nextForMultiAndDivade());
            case "min":
                return new Min(first, nextForMinMax());
            case "max":
                return new Max(first, nextForMinMax());
        
            default:
                throw new IllegalArgumentException();
        }
    }
    private MultiExpression parseNext() {
        if (take('-')) {
            return parsewithUnarMinus();
        } else if (take('t')) {
            take();
            return parsewithRightZeroes();
        } else if (take('l')) {
            take();
            return parsewithLeftZeroes();
        } else if (take('(')) {
            return parseElement();
        } else if (ch == 'x' || ch == 'y' || ch == 'z') {
            return parseVariable();
        } else {
            return parseConst(1);
        }
    }

    
    private MultiExpression parsewithLeftZeroes() {
        return new LeftZeroes(parseNext());
    }

    private MultiExpression parsewithRightZeroes() {
        return new RightZeroes(parseNext());
    }

    private MultiExpression parseElement() {
        int openscob = 1;
        while (take('(')) {
            openscob++;
        }
        MultiExpression first = parseNext();
        while (openscob != 0) {
            if (take(')')) {
                openscob--;
            } else {
                first = constract(first);
                //System.err.println(first);
            }
        }
        return first;
    }
    private MultiExpression nextForMultiAndDivade() {
        return parseNext();
    }
    private MultiExpression nextElforAddandSub() {
        MultiExpression first = parseNext();
        //System.err.println(first);
        while (ch == '*' || ch == '/') {
            first = constract(first);
            // System.err.println(first);
        }
        return first;
    }
    
    private MultiExpression nextForMinMax() {
        MultiExpression first = parseNext();
        //System.err.println(first);
        while (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            first = constract(first);
        }
        return first;
    }

    private MultiExpression parsewithUnarMinus() {
        if (ch == 'x' || ch == 'y' || ch == 'z') {
            return new UnarMinus(parseVariable());
        } else if (isAdiget()) {
            return parseConst(-1);
        }
        return new UnarMinus(parseNext());
    }

    private MultiExpression parseVariable() {
            return new Variable(Character.toString(take()));
    }

    private MultiExpression parseConst(int sign) {
        int val = 0;
        while (isAdiget()) {
            val = val * 10 + (take() - '0') * sign;
        }
        return new Const(val);
    }

    private boolean isAdiget() {
        return '0' <= ch && ch <= '9';
    }

    private void skipAllWaiteSpace() {
        StringBuilder sb = new StringBuilder();
        skipWaiteSpace();
        while (!end()) {
            sb.append(take());
            skipWaiteSpace();
        }
        this.string = sb.toString();
        this.pos = 0;
        take();
    }

    private void skipWaiteSpace() {
        while (Character.isWhitespace(ch) || System.lineSeparator().equals(Character.toString(ch))) {
            take();
        }
    }
    private String nextOper() {
        if (ch != 'm'){
            return Character.toString(take());
        } else {
            return Character.toString(take()) + Character.toString(take()) + Character.toString(take());
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
