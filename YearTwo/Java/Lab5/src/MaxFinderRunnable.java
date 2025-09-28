import java.util.Collections;
import java.util.Vector;

public class MaxFinderRunnable implements Runnable  {
    private final Vector<Integer> vector;
    private int max;

    public MaxFinderRunnable(Vector<Integer> vector) {
        this.vector = vector;
    }

    @Override
    public void run() {
        max = Collections.max(vector);
    }

    public int getMax() {
        return max;
    }
}
