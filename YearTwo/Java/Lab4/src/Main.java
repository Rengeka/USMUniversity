public class Main {
    public static void main(String[] args) {

        /*
        Простое обобщение: Создайте простой обобщённый класс Box<T>,
        который может хранить объект любого типа. Добавьте методы для
        установки и получения значения.
        Обобщённые методы: Добавьте в класс Box обобщённый метод compareTo(T other),
        где T должен реализовывать Comparable<T>. Метод будет сравнивать значения
        внутри двух коробок.
        */

        Box<Integer> intBox1 = new Box<Integer>(10);
        Box<Integer> intBox2 = new Box<Integer>(20);

        System.out.println( intBox1.compareTo(intBox2));

        System.out.println(intBox1.compareTo(intBox2));
        System.out.println(intBox2.compareTo(intBox1));
        System.out.println(intBox2.compareTo(intBox2));

        Box<Character> charBox3 = new Box<Character>('A');
        Box<Character> charBox4 = new Box<Character>('5');

        System.out.println(charBox3.compareTo(charBox4));
        System.out.println(charBox4.compareTo(charBox3));
        System.out.println(charBox4.compareTo(charBox4));
    }
}