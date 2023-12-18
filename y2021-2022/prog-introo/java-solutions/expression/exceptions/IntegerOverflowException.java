package expression.exceptions;

public class IntegerOverflowException extends RuntimeException{
    public IntegerOverflowException(String massage) {
        super(massage);
    }
}
