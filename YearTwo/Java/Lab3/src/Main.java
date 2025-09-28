public class Main {
    public static void main(String[] args) {
        //TIP Press <shortcut actionId="ShowIntentionActions"/> with your caret at the highlighted text
        // to see how IntelliJ IDEA suggests fixing it.

        /*Лабораторная работа №3. Обработка строк. Коллекции. Регулярные выражения.
        При решении задач использовать: класс String, StringBuffer, коллекции,
        настраиваемые коллекции, регулярные выражения.
        Избегать, по возможности, “мелкой” работы на уровне отдельных символов.

        Перечислить все слова заданного предложения, которые состоят из тех же букв,
        что и первое слово предложения.
        Между словами может быть произвольное число пробелов и знаков препинания.
        Вывести предложение и слова.
        */
        AnagramFinder.findAnagrams("add dad dadad 123 das!@@!#gdsad-DDA");
        AnagramFinder.findAnagrams("Hello ole !elloh ");
    }
}