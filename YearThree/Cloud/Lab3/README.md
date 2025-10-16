# Lab 3

## Задание

Создать две подсети внутри одного VPC. 

В публичной подсети расположить виртуальные машины с веб сервером и с bastion-хостом

В приватной подсети развернуть виртуальную машину с базой данных

Настроить NAT и IGW Gatway-и

Проверить подключение к виртаульным машинам через SSH (Bastion и db) и HTTP (Web server)

## Создание VPC

Маска /16 обозначает что 16 бит из 32 в ip адресе будут обозначать сеть

Нельзя выставить меньше 16 бит (Ограничение от AWS)

Default обозначает что мои инстансы будут использовать те же физичесике ресурсы что и инстансы других клиентов AWS

!["VPC"](./images/1.png)

## Создание IGW

Создаём IGW

!["VPC"](./images/2.png)

Аттачим его к VPC

!["VPC"](./images/3.png)

## Создаём публичную подсеть

Создадим публичную подсеть с адресом 10.3.1.0 и маской /24

И приватную подсеть с адресом 10.3.2.0 и маской /24

!["VPC"](./images/4.png)

!["VPC"](./images/5.png)

## Создание Route Table

Создаём публичную Route Table

!["VPC"](./images/6.png)

Аналогично создаём и приватную

Переходим к настройкам путей публичной подсети и указывает направление всего остального трафика к IGW

!["VPC"](./images/7.png)

Настраиваем ассоциации подсетей с route tables

!["VPC"](./images/8.png)

## Создание NAT Gateway

    NAT Gateway делает маппинг приватных адресов на публичные, позволяя выходить в сеть даже тем подсетям, у которых нет своего публичного ip

Создаём NAT

!["VPC"](./images/9.png)

И настраиваем приватную route table на перенаправление остального трафика на NAT Gateway

!["VPC"](./images/10.png)

## Создание Security Group

Создадим security группу, которая будет пропускать http/https трафик к веб серверу

!["VPC"](./images/11.png)

Создадим bastion security группу для подключения к приватной подсети через SSH

    Bastion - специальный шлюз для безопасного подключения к приватным ресурсам

!["VPC"](./images/12.png)

Создадим db security группу которая будет принимать трафик только из других security group

!["VPC"](./images/13.png)

## Создание EC2 инстансов

Создаём Amazon Linux t3.micro EC2 instance-ы с 8 GB памяти

Для начала для веб сервера

!["VPC"](./images/14.png)

В User Data вставляем скрипт

```bash
#!/bin/bash
dnf install -y httpd php
echo "<?php phpinfo(); ?>" > /var/www/html/index.php
systemctl enable httpd
systemctl start httpd
```

Потом для базы данных

!["VPC"](./images/15.png)

Добавляем в User Detail

```bash
#!/bin/bash
dnf install -y mariadb105-server
systemctl enable mariadb
systemctl start mariadb
mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED BY 'StrongPassword123!'; FLUSH PRIVILEGES;"
```

И bastion host инстанс

!["VPC"](./images/16.png)

С User Data

```bash
#!/bin/bash
dnf install -y mariadb105
```

## Проверка 

Проверяем веб сервер

!["VPC"](./images/17.png)

Проверяем bastion host. Подключаемся к нему через SSH

!["VPC"](./images/18.png)

И пингуем google.com чтобы понять есть ли доступ к интеренету изнутри виртуальной машины

Пытаемся подключиться к mysql

!["VPC"](./images/20.png)

Не получается. Это по тому, что в inbound rules стоит web-sg-k03, а не bastion-sg-k03, по этому чтобы проверить подключение к базе придётся либо менять security group либо ставить mysql клиент на web сервер. 

Подключимся по ssh к db виртуалке

!["VPC"](./images/21.png)