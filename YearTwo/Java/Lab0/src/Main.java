import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {

    /*Создать класс Matrix, содержащий двумерный массив n x m целого типа, организовать ввод-вывод массива,
    поиск минимального и максимального элементов. Для ввода использовать класс Scanner,
    а для вывода метод System.out.println().*/

    public static void main(String[] args) {
        Matrix matrix = new Matrix();
        System.out.println(matrix);


        Matrix mat = new Matrix(3,3);
        System.out.println(mat);

        mat.findMinElement();
        mat.findMaxElement();

        /*Matrix mat2 = new Matrix(scn);
        mat2.PrintValues();*/

        /*int[][] values = new int[][] { {1,2,3}, {4,5,6}, {7,8,9} };
        Matrix mat = new Matrix(values);
        mat.PrintValues();*/

        /*Matrix mat3 = new Matrix(3,2, scn);
        mat3.PrintValues();*/
    }
}