# Аттестация 1 по предмету Advanced Web Development (PHP)
 
## Репозиторий : https://github.com/Rengeka/University/tree/main/YearTwo/PHP/Attestaion1

## Запуск проекта

    1. Склонировать репозиторий с проектом.
    2. Установмит xampp
    3. Скопироват папку с проектом в xampp/htdocs
    4. Ввести в адресной строке браузера http://localhost/Attestation1/public/index.php

## Функционал приложения

    1. Возможность проходить тесты
    2. Возможность увидеть результат пройденного теста
    3. Возможность увидеть руезультаты других пользователей

## Структура теста 

    1. Название                 
    2. Вопрос об имени пользователя 
        Label для имени
    3. Вопрос 1
        a. Ответ 1          - Правильный
        b. Ответ 2
        c. Ответ 3
    4. Вопрос 2
        a. Ответ 1          - Правильный
        b. Ответ 2
        c. Ответ 3          - Правильный
    5. Вопрос 3
        a. Ответ 1
        b. Ответ 2
        c. Ответ 3          - Правильный
        d. Ответ 4
    6. Вопрос 4
        a. Ответ 1          - Правильный
        b. Ответ 2          - Правильный
        c. Ответ 3          - Правильный
    7. Вопрос 5
        a. Ответ 1
        b. Ответ 2          - Правильный
        c. Ответ 3

## Пример теста 

### Math Test
1. **What is 5 + 3?**
   - [ ] 6
   - [ ] 7
   - [x] 8
2. **Select all prime numbers.**
   - [x] 2
   - [ ] 4
   - [x] 5
3. **What is the square root of 16?**
   - [ ] 2
   - [x] 4
   - [ ] 8
4. **Which numbers are even?**
   - [ ] 1
   - [x] 2
   - [x] 6
   - [ ] 9
5. **What is 10 divided by 2?**
   - [ ] 2
   - [x] 5
   - [ ] 10

## Структура базы данных 

База данных находится в json фалах

results.db.json - файл с резульатами прохождения тестов

```json
[
    {
        "id": 1,
        "username": "user",
        "answers": [
            [
                "2"
            ],
            [
                "0"
            ],
            [
                "0"
            ],
            [
                "1",
                "2"
            ]
        ]
    },
]
```

tests.db.json - файл с самими тестами

```json
[
    {
    "id": 1,
    "title": "Math Test",
    "questions": [
      {
          "type": "radio",
          "text": "What is 5 + 3?",
          "options": ["6", "7", "8"],
          "correct": [2]
      },
      {
          "text": "Select all prime numbers.",
          "options": ["2", "4", "5"],
          "correct": [0, 2]
      },
      {
          "type": "radio",
          "text": "What is the square root of 16?",
          "options": ["2", "4", "8"],
          "correct": [1]
      },
      {
          "text": "Which numbers are even?",
          "options": ["1", "2", "6", "9"],
          "correct": [1, 2]
      },
      {
          "type": "radio",
          "text": "What is 10 divided by 2?",
          "options": ["2", "5", "10"],
          "correct": [1]
      }
    ]
  },
]
```

## Скриншоты работы приложения

![Alt text](/images/image.png "image")
![Alt text](/images/image2.png "image")
![Alt text](/images/image3.png "image")
![Alt text](/images/image4.png "image")
