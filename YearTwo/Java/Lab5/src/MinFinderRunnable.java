import java.util.Collections;
import java.util.Vector;

public class MinFinderRunnable implements Runnable {
    private final Vector<Integer> vector;
    private int min;

    public MinFinderRunnable(Vector<Integer> vector) {
        this.vector = vector;
    }

    @Override
    public void run() {
        min = Collections.min(vector);
    }

    public int getMin() {
        return min;
    }
}
