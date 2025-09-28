# JSIndWork2
 
1. Инструкции по запуску проекта : 
Скопировать репозиторий - git clone https://github.com/Rengeka/JSIndWork2.git Запустить файл index.js из папки src

2. Описание лабораторной работы : 
Условия работы - https://github.com/MSU-Courses/javascript_typescript/blob/main/lab/LI2/JS02.md

3. Краткая документация к проекту : 
файл activity.js содержит функции, изымающие случайную активность с сайта https://www.boredapi.com/api/activity
Функиця getRandomActivity посылает запрос на сайти, получает промис, разрешает его и возвращает json-а
Функция getRandomActivityAsync аналогична функции getRandomActivity, но выполняется асинхронно. Конструкцией try-catch она отправляет запрос и возвращает данные в виде json-а

Функции updateActivity и updateActivityAsync вызывают функции getRandomActivity и getRandomActivityAsync соответственно. Получая данные об активности, эти функции выводят их на html страницу

4. Примеры использования проекта с приложением скриншотов или фрагментов кода:

    // Для неасинхронной функции
    updateActivity();
    setInterval(updateActivity, 1000);

    // Для асинхронной функции
    updateActivityAsync();
    setInterval(updateActivityAsync, 1000);
5. Ответы на контрольные вопросы:
i.      Какое значение возвращает функция fetch?
            Функция fetch возвращает promise

ii.     Что представляет собой Promise?
            Промис - это объект JavaScript, который используется для выполнения асинхронных операций
            Промис - это обещание получения ответа

iii.    Какие методы доступны у объекта Promise?
            then, catch, finally
            Другие методы, не изучаемые в рамках курса

6. Список использованных источников : 
https://developer.mozilla.org/ru/docs/Web/JavaScript
https://www.w3schools.com/