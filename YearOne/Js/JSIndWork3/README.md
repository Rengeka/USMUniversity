# JSIndWork3
 
1. Инструкции по запуску проекта : 
Скопировать репозиторий - git clone https://github.com/Rengeka/JSIndWork3.git Запустить файл index.js из папки src

2. Описание лабораторной работы : 
Условия работы - https://github.com/MSU-Courses/javascript_typescript/blob/main/lab/LI3/JS03.md

3. Краткая документация к проекту : 
файл index.js содержит класс transaction и осуществляет операции с транзакциями.
Файл style.css содержит стили, применяемые в index.html
Файл transactions.json содержит базу транзацкций

5. Ответы на контрольные вопросы :
    1.  Каким образом можно получить доступ к элементу на веб-странице с помощью JavaScript?
        ```
        const element = document.getElementById("Id"); // По ID элемента
        const element = document.querySelector(".Class"); // Посредством querry селектора по css стилю
        const elements = document.getElementsByClassName("Class"); // Получение всех элементов определённого класса
        const elements = document.getElementsByTagName("div"); // Получение всех элементов определенного типа
    2.  Что такое делегирование событий и как оно используется для эффективного управления событиями на элементах DOM?
        Делегирование событий - добавление обработчик событий к родительскому элементу, который будет реагировать на события, происходящие в его дочерних элементах. Это позволяет эффективно управлять событиями для элементов, которые могут быть добавлены или удалены из DOM дерева.

        ```
        // Пример обработчика события click из моего кода
        table.addEventListener('click', (event) => {
            const id = event.target.closest("tr").id;
            ShowTransactionData(transactions.find((transaction) => transaction.id == id));
        });
    3.  Как можно изменить содержимое элемента DOM с помощью JavaScript после его выборки?
        Изменение содержимого элемента DOM возможно, обновлением его свойств

        ```
        // Прмер изменения свойств элемента в моём коде
        function ShowTransactionData(transaction) {
            const dataContainer = document.getElementById('transaction-data');
            console.log(dataContainer)

            // Изменение свойства textContent
            dataContainer.textContent = `ID: ${transaction.id}, Дата: ${transaction.date}, Сумма: ${transaction.amount}, Категория: ${transaction.category}, Описание: ${transaction.description}`;
        }
    4.  Как можно добавить новый элемент в DOM дерево с помощью JavaScript?
        
        ```
        // Пример создания и добавления элемента на страницу в моём коде
        let td1 = document.createElement("td");
        tr.appendChild(td1);
