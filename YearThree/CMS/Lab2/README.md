# Lab 2

## Цель работы
Научиться устанавливать WordPress в локальной среде, осваивать админ-панель, изменять внешний вид сайта через темы и расширять его функциональность с помощью плагинов.

## Подготовка среды
Создадим docker-compose.yaml
```yaml
version: "3.9"

services:
  db:
    image: mariadb:11.4
    container_name: wordpress_db
    restart: always
    environment:
      MARIADB_DATABASE: wordpress
      MARIADB_USER: wp_user
      MARIADB_PASSWORD: wp_password
      MARIADB_ROOT_PASSWORD: root_password
    volumes:
      - db_data:/var/lib/mysql

  wordpress:
    image: wordpress:php8.3-apache
    container_name: wordpress_app
    restart: always
    ports:
      - "8080:80"
    environment:
      WORDPRESS_DB_HOST: db:3306
      WORDPRESS_DB_NAME: wordpress
      WORDPRESS_DB_USER: wp_user
      WORDPRESS_DB_PASSWORD: wp_password
    depends_on:
      - db
    volumes:
      - wp_data:/var/www/html

volumes:
  db_data:
  wp_data:
```

Поднимем контейнеры при помощи ```docker-compose up```

## Первоначальная настройка сайта

Выбираем язык

![1](images/1.png)

Настраиваем сайт и админа

![2](images/2.png)

Настраиваемчасовой пояс

![3](images/3.png)

Настраиваем Permalinks

![19](images/19.png)

## Работа с темами

Устанавливаем тему из официального каталога

![4](images/4.png)

Выбираем тему

![5](images/5.png)

Пробуем другую тему чтобы увидеть разницу

![6](images/6.png)

Настраиваем логотип

![7](images/7.png)

![8](images/8.png)

Настраиваем тэг

![9](images/9.png)

Можем настроить свои цвета

![10](images/10.png)

## Работа с плагинами

Устанавливаем плаигны

![11](images/11.png)

![12](images/12.png)

Активируем их

![13](images/13.png)

Проверяем что меняется при активации и деактивации плагина

![14](images/14.png)

![15](images/15.png)

## Создание контента

Настроим страницу с формой для обратной связи

![16](images/16.png)

Создадим несколько постов

![17](images/17.png)

![18](images/18.png)

## Контрольные вопросы

### Что делает тема в WordPress, а что — плагин?

Тема отвечает за внешний вид сайта:

1. Дизайн страниц

2. Расположение элементов

3. Цвета, шрифты

4. Шаблоны постов и страниц

Плагин добавляет функциональность сайту:

1. Формы обратной связи

2. SEO-оптимизацию

3. Интернет-магазин

4. Безопасность

5. Кэширование

### Почему при смене темы контент сайта не теряется?

Контент сайта (посты, страницы, изображения, комментарии) хранится в базе данных WordPress, а не в теме.

Тема только отображает этот контент, поэтому при её смене данные остаются, просто меняется их оформление.

### Как можно изменить внешний вид сайта без редактирования кода?

В WordPress это можно сделать несколькими способами:

1. Через кастомайзер темы (Настройка / Customize)

2. Используя готовые темы

3. Через конструкторы страниц (например, Elementor)

4. С помощью блоков редактора Gutenberg

4. Серез настройки темы (Theme Options)