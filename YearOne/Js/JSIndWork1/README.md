# JSIndWork1

1. Инструкции по запуску проекта
    Скопировать репозиторий - git clone https://github.com/Rengeka/JSIndWork1.git
    Запустить файл index.js

2. Описание лабораторной работы
   Условия работы - https://github.com/MSU-Courses/javascript_typescript/blob/main/lab/LI1/JS01.md

3. Краткая документация к проекту
    В файле transactions.json находится список транзакций. 
    Класс TransactionAnalyzer получает данные из этого json-файла и записывает данные в поле transactions
    Методы I - XV - это функции, что реализуют конкретные условия работы 

4. Примеры использования проекта с приложением скриншотов или фрагментов кода

    Пример использования каждой из функций:

        const trAnlyzer = new TransactionAnalyzer();

        console.log(trAnlyzer.getUniqueTransactionType());
        console.log(trAnlyzer.calculateTotalAmount());
        console.log(trAnlyzer.calculateTotalAmountByDate("2019", "04",  "30"));
        console.log(trAnlyzer.getTransactionByType("debit"));
        console.log(trAnlyzer.getTransactionsInDateRange("2019-04-20", "2019-04-25"));
        console.log(trAnlyzer.getTransactionsByMerchant("SandwichShopXYZ"));
        console.log(trAnlyzer.calculateAverageTransactionAmount());
        console.log(trAnlyzer.getTransactionsByAmountRange(30, 60));
        console.log(trAnlyzer.calculateTotalDebitAmount());
        console.log(trAnlyzer.findMostTransactionsMonth());
        console.log(trAnlyzer.findMostDebitTransactionMonth());
        console.log(trAnlyzer.mostTransactionTypes());
        console.log(trAnlyzer.getTransactionsBeforeDate("2019-01-03"));
        console.log(trAnlyzer.findTransactionById(1));
        console.log(trAnlyzer.mapTransactionDescriptions());

5. Ответы на контрольные вопросы

    a. Примитивные типы данных в JavaScript:

        Числа (Numbers): Целые числа и числа с плавающей запятой.
        Строки (Strings): Последовательности символов, заключенные в кавычки.
        Логические значения (Booleans): true или false.
        Undefined: Значение, представляющее отсутствие значения.
        Null: Значение, представляющее отсутствие или пустое значение.
        Символы (Symbols): Уникальные и неизменяемые значения, используемые в качестве идентификаторов свойств объекта.
        BigInt: Числа произвольной точности.

    b. Методы массивов, использованные в приложении:

        push(): Для добавления элементов в конец массива.
        forEach(): Для выполнения функции для каждого элемента массива.
        filter(): Для создания нового массива с элементами, отфильтрованными согласно заданному условию.
        find(): Для поиска первого элемента массива, удовлетворяющего заданному условию.
        indexOf(): Для поиска индекса заданного элемента в массиве.
        slice(): Для создания нового массива, содержащего копию части исходного массива.
        length: Свойство, возвращающее количество элементов в массиве.
        Эти методы были использованы для обработки данных о транзакциях, таких как фильтрация по типу транзакции, поиск по дате и мерчанту, вычисление общей суммы и т. д.

    c. Роль конструктора класса:

        Конструктор класса используется для инициализации новых экземпляров класса. Он определяет, какие свойства и методы будут доступны в каждом экземпляре класса при его создании. В конструкторе обычно инициализируются свойства объекта, а также могут выполняться другие действия, необходимые при создании экземпляра.

    d. Создание нового экземпляра класса в JavaScript:

        Экземпляр класса создается с помощью оператора new, за которым следует имя конструктора класса и необходимые аргументы (если они требуются)

6. Список использованных источников
    https://developer.mozilla.org/ru/docs/Web/JavaScript  
    https://www.w3schools.com/  

