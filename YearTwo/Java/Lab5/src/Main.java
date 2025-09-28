import java.util.*;

public class Main {
    public static void main(String[] args) throws InterruptedException {

        /*
        Требования к программе:

        1.    Данные вводятся с клавиатуры. Имеется защита от неправильного ввода.
        2.    Исходные данные и результат выводятся на экран монитора.
        3.    Программа тестируется на нескольких различных примерах.
        4.    Работа в параллельных процессах не дублируется.
              Вычислительная нагрузка на каждый процесс примерно одинакова.
        5.    Результаты выводить в процессе main.
              В начале программы вывести на консоль число доступных процессоров на компьютере.

        1.    Написать программу на Java с двумя нитями процессов:
                1-ый процесс ищет в векторе максимальный элемент;
                2-ой процесс ищет в векторе минимальный элемент
        */


        System.out.println("Available threads : " + Runtime.getRuntime().availableProcessors() );

        Vector<Integer> vector = new Vector<>();
        Scanner in = new Scanner(System.in);

        System.out.println("Type all values of vector");
        System.out.println("Type end if you want to stop");

        while (true){
            if(in.hasNextInt()){
                vector.add(in.nextInt());
            }
            else if(in.next().equals("end")){
                break;
            }
            else{
                System.out.println("Invalid input. Try again");
            }
        }

        System.out.println("Your vector is : " + vector);

        var maxRunnable = new MaxFinderRunnable(vector);
        var minRunnable = new MinFinderRunnable(vector);

        Thread maxThread = new Thread(maxRunnable);
        Thread minThread = new Thread(minRunnable);

        maxThread.start();
        minThread.start();

        maxThread.wait();
        System.out.println("Max element : " + maxRunnable.getMax());

        minThread.wait();
        System.out.println("Min element : " + minRunnable.getMin());
    }
}