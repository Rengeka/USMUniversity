public class Box<T extends Comparable<T>> /*implements Comparable<Box<T>>*/ {
    private T value;

    public Box(T value) {
        this.value = value;
    }

    public T getValue() {
        return value;
    }

    public void setValue(T value) {
        this.value = value;
    }

    public int compareTo(Box<T> other) {
        return value.compareTo(other.getValue());
    }
}
