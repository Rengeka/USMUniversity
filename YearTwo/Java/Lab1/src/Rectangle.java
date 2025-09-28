import java.util.Scanner;

public class Rectangle extends Side{
    protected int width;

    Rectangle(int length, int width) {
        this.length = length;
        this.width = width;
    }


    public int getArea(){
        return width * length;
    }

    @Override public String toString(){
        return "[Length : " + length + ", Width : " + width + " ]";
    }

}
