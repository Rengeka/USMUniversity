# Лабораторная работа IWNO5: Взаимодействие контейнеров

## Цель работы
Выполнив данную работу студент сможет управлять взаимодействием нескольких контейнеров.

## Задание
Создать php приложение на базе двух контейнеров: nginx, php-fpm.

## Выполнение

Создадим репозиторий containers06 

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

Создадим докерфайлы для php и nginx с указанием монтируемых томов и базовых образов

nginx: Открываем порт 80

![Alt text](/images/Снимок%20экрана%202025-03-30%20110603.png "image")

php:

![Alt text](/images/Снимок%20экрана%202025-03-30%20110553.png "image")


Создаём сеть internal 

```
    docker network create internal
```

Билдим наши image

```
    docker build -f Dockerfile-php backend .
    docker build -f Dockerfile-nginx frontend .
```

Запускаем контейнеры в сети internal 

![Alt text](/images/Снимок%20экрана%202025-03-30%20110345.png "image")

Стучимся на сервер и проверяем работоспособность 

![Alt text](/images/Снимок%20экрана%202025-03-30%20101617.png "image")

![Alt text](/images/Снимок%20экрана%202025-03-30%20110316.png "image")

## Ответы на вопросы

### Каким образом в данном примере контейнеры могут взаимодействовать друг с другом?

    Контейнервы взаимодействуют друг с другом посредство сети internal. Контейнер nginx обращается к контейнеру backend по порту 9000 (Что мы указывали в конфиг файле "fastcgi_pass backend:9000;")

### Как видят контейнеры друг друга в рамках сети internal?

    Контейнервы видят друг друга по именам

### Почему необходимо было переопределять конфигурацию nginx?

    Для указания нашего backend контейнера и переопределения пути к index.php (Только в моём случае т.к структура php проекта другая)