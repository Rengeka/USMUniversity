//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {

    /*Создайте иерархию классов Сторона – Прямоугольник – Тумбочка с одной полкой. Класс Прямоугольник должен содержать метод
    для вычисления площади прямоугольника. Класс Тумбочка должен содержать метод для определения вместимости.
    Последние два класса в иерархии должны иметь конструкторы. Создайте метод MAIN, в котором создается 2 прямоугольника
    (т.е. 2 объекта класса Прямоугольник), определяется какой из прямоугольников больше и сколько раз меньший прямоугольник
    входит в больший. Необходимо также показывать все характеристики создаваемых объектов.*/


    public static void main(String[] args) {
        OneShelfTable table1 = new OneShelfTable(10, 10, 20);
        OneShelfTable table2 = new OneShelfTable(20, 12, 50);

        System.out.println(table1.length);

        compareTables(table1, table2);
    }

    public static void compareRectangles(Rectangle rect1, Rectangle rect2)
    {
        if(rect1.getArea() > rect2.getArea()){
            System.out.println("Rectangle 1 is larger than Rectangle 2");
            System.out.println("Rectanle 1 can fit Rectangle 2 " + (rect1.getArea() / rect2.getArea()) + " times");
        }
        else if(rect1.getArea() < rect2.getArea()){
            System.out.println("Rectangle 2 is larger than Rectangle 1");
            System.out.println("Rectanle 2 can fit Rectangle 1 (" + (rect2.getArea() / rect1.getArea()) + ") times");
        }
        else{
            System.out.println("Rectangles are equal");
        }
    }

    public static void compareTables(OneShelfTable table1, OneShelfTable table2)
    {
        if(table1.getCapacity() > table2.getCapacity()){
            System.out.println("Table 1 is larger than Table 2");
            System.out.println("Table 1 can fit Table 2 " + (table1.getCapacity() / table2.getCapacity()) + " times");
        }
        else if(table1.getArea() < table2.getArea()){
            System.out.println("Table 2 is larger than Table 1");
            System.out.println("Table 2 can fit Table 1 (" + (table2.getCapacity() / table1.getCapacity()) + ") times");
        }
        else{
            System.out.println("Tables are equal");
        }
    }
}

