public class OneShelfTable extends Rectangle {
    private final int height;

    OneShelfTable(int length, int width, int height) {
        super(length, width);
        this.height = height;
    }

    public int getCapacity() {
        return getArea() * height;
    }

    @Override public String toString(){
        return "[Length : " + length + ", Width : " + width + ", Height : " + height + "]";
    }
}
