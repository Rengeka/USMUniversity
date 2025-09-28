public class NotPrimaryNumberException extends Exception {
    // Exception message
    public NotPrimaryNumberException(String message) {
        super(message);
    }

    public NotPrimaryNumberException()
    {
        super("Entered number is not simple");
    }
}
