# Лабораторная работа №1. Виртуальный сервер
**Имя и фамилия**: Stanislav Ciobanu

**Группа**: I2302

**Дата выполнения**: 11.02.2025

## Описание задачи

**Задача** - Установить debian на виртуальную машину QEMU и настройка HTTP сервера для ознакомления с основами виртуализации и администрирования серверов.

# Подготовка:

Скачиваем серверный Debian x64 и систему виртуализации QEMU 
 
![Alt text](/screenshots/Снимок%20экрана%202025-02-07%20214623.png "image")

# Выполнение:

    Создаём папку lab01. 
    В ней создаём папку dvd и файл readme.md
    В папку dvd помещаем iso образ debian

    Командой создаём debian.qcow2 файл необходимый для виртуализации

```bash
    qemu-img create -f qcow2 debian.qcow2 8G 
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-08%20151605.png "image")
![Alt text](/screenshots/Снимок%20экрана%202025-02-08%20151729.png "image")

    Командой запускаем нашу 64-разрядную виртуальную машину архитектуры x86 для нашего qcow2 образа

```bash
    qemu-system-x86_64 -hda debian.qcow2 -cdrom dvd/debian.iso -boot d -m 2G
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-08%20151808.png "image")

# Установка:

    Задаём юзера, пароль, язык системы и.др

![Alt text](/screenshots/Снимок%20экрана%202025-02-08%20152549.png "image")
![Alt text](/screenshots/Снимок%20экрана%202025-02-08%20152638.png "image")
![Alt text](/screenshots/Снимок%20экрана%202025-02-08%20155216.png "image")

    Выключаем виртуальную машину и выполняем команду для повторного запуска

```bash
    qemu-system-x86_64 -hda debian.qcow2 -m 2G -smp 2 \
    -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::1080-:80,hostfwd=tcp::1022-:22
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20165647.png "image") 

    Заходим под учётную запись созданного пользователя

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20165751.png "image")

    Входим в sudo режим и под root правами скачиваем необходимые пакеты

```bash
    su
    apt update -y
    apt install -y apache2 php libapache2-mod-php php-mysql mariadb-server mariadb-client unzip
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20170437.png "image")

    Возникла проболема. Для её решения ввручную укажем репозитории в config файле
    Я выбрал американский репозиторий, но логичнее брать тот, что находится географически близко

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20174203.png "image")
![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20173910.png "image")

    Скачиваем пакеты 

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20174043.png "image")

    Cкачиваем PhpMyAdmin и CMS Drupal 

```bash
    wget https://files.phpmyadmin.net/phpMyAdmin/5.2.2/phpMyAdmin-5.2.2-all-languages.zip
    wget https://ftp.drupal.org/files/projects/drupal-11.1.1.zip

    ls -l
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20174454.png "image")

    Распаковываем архивы в соответствующие папки

```bash
    mkdir /var/www
    unzip phpMyAdmin-5.2.2-all-languages.zip
    mv phpMyAdmin-5.2.2-all-languages /var/www/phpmyadmin
    unzip drupal-11.1.1.zip
    mv drupal-11.1.1 /var/www/drupal
```

    Создаём базу данных  drupal_db

```bash
    mysql -u root
    CREATE DATABASE drupal_db;
    CREATE USER 'user'@'localhost' IDENTIFIED BY 'password';
    GRANT ALL PRIVILEGES ON drupal_db.* TO 'user'@'localhost';
    FLUSH PRIVILEGES;
    EXIT;
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20180016.png "image")
![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20180316.png "image")

    В папке /etc/apache2/sites-available создаём файл 01-phpmyadmin.conf
    В папке /etc/apache2/sites-available создаём файл 02-drupal.conf

```bash
    nano /etc/apache2/sites-available/01-phpmyadmin.conf

    <VirtualHost *:80>
        ServerAdmin webmaster@localhost
        DocumentRoot "/var/www/phpmyadmin"
        ServerName phpmyadmin.localhost
        ServerAlias www.phpmyadmin.localhost
        ErrorLog "/var/log/apache2/phpmyadmin.localhost-error.log"
        CustomLog "/var/log/apache2/phpmyadmin.localhost-access.log" common
    </VirtualHost>

    nano /etc/apache2/sites-available/02-drupal.conf

    <VirtualHost *:80>
        ServerAdmin webmaster@localhost
        DocumentRoot "/var/www/drupal"
        ServerName drupal.localhost
        ServerAlias www.drupal.localhost
        ErrorLog "/var/log/apache2/drupal.localhost-error.log"
        CustomLog "/var/log/apache2/drupal.localhost-access.log" common
    </VirtualHost>  
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20181232.png "image")
![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20182603.png "image")

    Зарегистрируем конфигурации и перезапустим Apache HTTP Server, выполнив команды

```bash
    /usr/sbin/a2ensite 01-phpmyadmin
    /usr/sbin/a2ensite 02-drupal

    systemctl reload apache2
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20183015.png "image")

    Добавим в файл /etc/hosts строки

```bash
    127.0.0.1 phpmyadmin.localhost
    127.0.0.1 drupal.localhost
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20183617.png "image")

    Выполинм uname -a и попробуем постучаться на наш localhost по адресам  http://drupal.localhost:1080 и http://phpmyadmin.localhost:1080
 
```bash
    uname -a
```

![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20183649.png "image")
![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20183727.png "image")
![Alt text](/screenshots/Снимок%20экрана%202025-02-09%20183746.png "image")

# Ответы на вопросы:
# 1.  Каким образом можно скачать файл в консоли при помощи утилиты wget?

    Ответ: Необходимо вызвать утилиту wget с аргументом в виде URL адреса файла
# 2.  Зачем необходимо создавать для каждого сайта свою базу и своего пользователя?

    a.  Безопасность - Только владелец сайта будет иметь доступ к данным пользователя.
        Если необходима возможность авторизироваться одними и теми же данными на разных сайтах,
        следует воспользоваться стандартом OpenID

    b.  Данные сайтов разделяются. Каждый сайт может хранить только необходимую ему информацию о пользователе и ничего лишнего

# 3.  Как поменять доступ к системе управления БД на порт **1234**?
    
    Ответ: Каталог /etc содержит конфигурационные файлы всех утилит и программ. В каталоге /etc/mysql содержится всё, что касается
    базы mysql. Там присутствуют mariadb.cnf и my.cnf, в которых можно изменить значение порта (# port = 3306) на необходимое.

# 4.  Какие преимущества, с вашей точки зрения, даёт виртуализация?

    Виртуализация позволяет создать эмуляции иного устройства. Это может быть полезно не только при настройке веб-сервисов,
    но и при разработке ПО для спецефических устройств, обладающих иной архитектурой. Так-же виртуализация позволяет запустить 
    другую операционную систему и при этом даёт инструменты по контролю ресурсов, выделяемых под виртуальную машину.

# 5.  Почему важно настроить время?

    TLS и SSL сертификаты зависят от времени, следовательно для настройки безопасного подключения потребуется конкретно настрокенная система. 
    Время необходимо для корректного логирования, а так же, вероятно, может требоваться по юридическим причинам.  

# 6.  Сколько места занимает установленная вами ОС (виртуальный диск) на хостовой машине?

    2,41 GB памяти.

# 7.  Какие есть рекомендации по разбиению диска для серверов? Почему рекомендуется так разбивать диск?

    В первую очередь разбивать диск необходимо, чтобы выделить конкретное количество памяти для разных секций (каталогов).
    Разные партиции могут очень сильно отличаться, вплоть до типа файловой системы, каждая из которых служит каким-либо конкретным целям и 
    может подходить лучше или хуже в зависимости от случая. 
    Само монтирование разделов зависит от задачи которой служит виртуальная машина. Непример выделение раздела swap позволит
    использовать статическую память, как оперативную. Это замедлит скорость, но увелисит общий объём памяти.
    Монтировка отдельных разделов в папки home, etc, var и.т.д позволит отделить важные каталоги. Так-же разделы
    легче форматировать, чем целый диск (или виртуальный).

# Выводы

В результате работы мы создали виртуальную машину на базе дистрибутива debian и запустили на ней простейший веб-сервер.
Работа дала базовое представление о прикладном значекнии понятия "виртауализация" и научила запускать и тестировать веб-сервер в безопасной
и чётко контролируемой среде. 
