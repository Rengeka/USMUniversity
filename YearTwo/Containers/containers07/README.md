# Лабораторная работа №6: Создание многоконтейнерного приложения

## Цель работы
Ознакомиться с работой многоконтейнерного приложения на базе docker-compose.

## Задание
Создать php приложение на базе трех контейнеров: nginx, php-fpm, mariadb, используя docker-compose.

## Выполнение

Создадим репозиторий containers07

Создадим внутри директорию mounts/site и скопирую свой php проект https://github.com/Rengeka/University/tree/main/YearTwo/PHP/Attestaion1

Создадим .gitignore файл и добавим в него строку, чтобы не коммитить php проект 

```gitignore
    mounts/site/*
```

Создаём директорию nginx с конфиг файлом default.conf 

```
server {
    listen 80;
    server_name _;
    root /var/www/html;
    index index.php;
    location / {
        try_files $uri $uri/ /index.php?$args;
    }
    location ~ \.php$ {
        fastcgi_pass backend:9000;
        fastcgi_index index.php;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        include fastcgi_params;
    }
}
```

Изменим строку root ```/var/www/html;``` на ```/var/www/html/public``` т.к там находится мой index.php

![Alt text](/images/Снимок%20экрана%202025-04-06%20104222.png "image")

Создадим файл docker-compose.yml с указанием всех наших сервисов

![Alt text](/images/Снимок%20экрана%202025-04-06%20104209.png "image")

Запускаем docker-compose.yml

![Alt text](/images/Снимок%20экрана%202025-04-06%20104917.png "image")

Стучимся на localhost чтобы увидеть что наш сервер запущен и можно получить доступ к сайту.

![Alt text](/images/Снимок%20экрана%202025-04-06%20105136.png "image")

## Ответы на вопросы

### В каком порядке запускаются контейнеры?

![Alt text](/images/Снимок%20экрана%202025-04-06%20105620.png "image")

Как видно из логов, контейнеры каждый раз запускаются в произвольном порядке. Докер сам решает, как их запускать. Иногда это может вызывать проблемы, в таком случае придётся явно указывать порядок запуска контейнеров.

### Где хранятся данные базы данных?

В томе db_data, созданном докером

### Как называются контейнеры проекта?

containers07_database_1
containers07_backend_1
containers07_frontend_1

Имя выбирается как имя контейнера + имя сервиса + номер

### Вам необходимо добавить еще один файл app.env с переменной окружения APP_VERSION для сервисов backend и frontend. Как это сделать?

Создаём app.env файл

Добавляем APP_VERSION=1.0.0

В docker-compose.yml для наших сервисов backend, frontend добавляем 

```
    env_file:
        - mysql.env
        - app.env
```