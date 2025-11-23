# Lab 6

## Цель работы 
Закрепить навыки работы с AWS EC2, Elastic Load Balancer, Auto Scaling и CloudWatch, создав отказоустойчивую и автоматически масштабируемую архитектуру.

Студент развернёт:

1. VPC с публичными и приватными подсетями;
2. Виртуальную машину с веб-сервером (nginx);
3. Application Load Balancer;
4. Auto Scaling Group (на основе AMI);
5. Нагрузочный тест с использованием CloudWatch.

## Выполнение 

Создадим VPC с 2 приватными и 2 публичными подсетями, gateway-ем и nat-gateway-ем через VPC Wizard

!["VPC"](./images/1.png)

Создадим EC2 инстанс. 

Настраиваем его в соответствиями с условиями лабораторной работы
![alt text](image.png)
!["EC2"](./images/3.png)
!["EC2"](./images/4.png)
!["EC2"](./images/5.png)
!["EC2"](./images/6.png)

Ждём пока виртуальная машина запустится и создаём AMI

!["AMI"](./images/7.png)

Создадим Launch Tempalte

!["LT"](./images/8.png)

Важно указать ту же SG но при этом не указывать конркетную подсеть

Создадим Target Group

!["TG"](./images/9.png)

Создадим Load Balancer

!["LB"](./images/10.png)

Выбираем обе подсети 

!["LB"](./images/11.png)

Указываем созданную Target Group

!["LB"](./images/12.png)

Создадим Auto Scaling Group

!["LB"](./images/13.png)

!["LB"](./images/14.png)

!["LB"](./images/15.png)

!["LB"](./images/16.png)

Проверяем

!["LB"](./images/17.png)

!["LB"](./images/18.png)

Запускаем curl.sh

!["LB"](./images/19.png)

Удаляем ресурсы