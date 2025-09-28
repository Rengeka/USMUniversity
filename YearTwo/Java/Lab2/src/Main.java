import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {

        /* 1. Лабораторная работа №2. Создание и обработка собственных исключений.

        В программе требуется:

        ·        Создать собственное исключение (class).

        ·        Создать метод (throw), который может возбуждать это исключение(throws).

        ·        Написать метод, перехватывающий и обрабатывающий исключение (try-catch), возбуждаемое другим методом.

        Исключение: с консоли вводятся 10 чисел и записываются в массив. Добиться ввода только простых чисел.*/


        Scanner scn = new Scanner(System.in);
        int[] arr = new int[10];

        InputArray(arr, scn);
        PrintArray(arr);

    }

    public static void InputArray(int[] arr, Scanner scn) {
        for(int i = 0; i < arr.length; i++){
            arr[i] = scn.nextInt();

            try {
                Main.CheckIfIsPrimary(arr[i]);
            }
            catch (Exception e) {
                System.out.println(e.getMessage());
                i--;
            }
        }
    }

    public static void CheckIfIsPrimary(int num) throws Exception{

        // Checking if is Rational
        if (!(num < 1)){

            // Iterating number until finding divider or reaching square root
            for (int i = 2; i <= Math.sqrt(num); i++){
                if (num % i == 0){
                    // Throwing exception
                    throw new NotPrimaryNumberException("Not primary number exception. It divides on " + i);
                }
            }
        }
        else{
            throw new Exception("Not rational number exception");
        }
    }

    public static void PrintArray(int[] arr)
    {
        for (int i = 0; i < arr.length; i++){
            System.out.print(arr[i] + " ");
        }
    }
}