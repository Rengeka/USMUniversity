# Лабораторная Работа 3

## Требования

1. Создать 2 виртуальыне машины
2. На VM1 развернуть базу данных, zabbix-server и zabbix-web интерфейс
3. На VM2 установить zabbix агента и настроить мониторинг

## Реализация

Я использовал Hashicorp vargant для создания виртуальных машин

Создаём Vagrantfile с 2 виртуалками
```bash
Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/jammy64"
  config.vm.provider "virtualbox" do |vb|
    vb.memory = 1024 
    vb.cpus = 1
  end

config.vm.define "vm1" do |vm1|
  vm1.vm.hostname = "vm1"
  vm1.vm.network "private_network", ip: "192.168.56.10"


config.vm.define "vm2" do |vm2|
    vm2.vm.hostname = "vm2"
    vm2.vm.network "private_network", ip: "192.168.56.11"
```

Для первой виртуалки создаём Docker-compose.yaml 

```yaml
version: '3.9'

services:
  zabbix-mysql:
    image: mysql:8.0
    container_name: zabbix-mysql
    command: >
      --default-authentication-plugin=mysql_native_password
      --character-set-server=utf8mb4
      --collation-server=utf8mb4_unicode_ci
    environment:
      MYSQL_DATABASE: zabbix
      MYSQL_USER: zabbix
      MYSQL_PASSWORD: zabbix-pwd
      MYSQL_ROOT_PASSWORD: root-pwd
    volumes:
      - zabbix-mysql-data:/var/lib/mysql
    networks:
      - zabbix-net
    ports:
      - "3306:3306"
    healthcheck:
      test: ["CMD", "mysqladmin", "ping", "-h", "localhost"]
      interval: 5s
      retries: 10
      timeout: 5s

  zabbix-server:
    image: zabbix/zabbix-server-mysql:6.4.0-ubuntu
    container_name: zabbix-server
    depends_on:
      zabbix-mysql:
        condition: service_healthy
    environment:
      DB_SERVER_HOST: zabbix-mysql
      MYSQL_DATABASE: zabbix
      MYSQL_USER: zabbix
      MYSQL_PASSWORD: zabbix-pwd
      MYSQL_ROOT_PASSWORD: root-pwd
    ports:
      - "10051:10051"
    networks:
      - zabbix-net

  zabbix-web:
    image: zabbix/zabbix-web-nginx-mysql:6.4.0-ubuntu
    container_name: zabbix-web
    depends_on:
      zabbix-server:
        condition: service_started
    environment:
      ZBX_SERVER_HOST: zabbix-server
      DB_SERVER_HOST: zabbix-mysql
      MYSQL_DATABASE: zabbix
      MYSQL_USER: zabbix
      MYSQL_PASSWORD: zabbix-pwd
      MYSQL_ROOT_PASSWORD: root-pwd
    ports:
      - "8080:8080"
    networks:
      - zabbix-net

volumes:
  zabbix-mysql-data:

networks:
  zabbix-net:
    driver: bridge
```

В Vargantfile добавляем копирование и запус docker-compose файла на первой виртуалке
```bash
    vm1.vm.synced_folder "./vm1_data", "/home/vagrant/vm1_data"

    vm1.vm.provision "shell", inline: <<-SHELL
      sudo apt update -y
      sudo apt install -y docker.io docker-compose
      sudo systemctl enable --now docker

      cd /home/vagrant/vm1_data
      sudo docker-compose up -d
    SHELL
```

На второй виртулаке запускаем только контейнер с агентом
```bash
    vm2.vm.provision "shell", inline: <<-SHELL
      sudo apt update -y
      sudo apt install -y docker.io

      sudo docker run -d --name zabbix-agent \
        -e ZBX_SERVER_HOST=192.168.56.10 \
        -e HOSTNAME=vm2 \
        -p 10050:10050 \
        zabbix/zabbix-agent:alpine-7.0-latest
    SHELL
```

Запускаем ```vagrant up```

Заходим на http://192.168.56.10:8080 

Вводим логин Admin и пароль zabbix

Заходим во вкладку Monitoring->Hosts и добавляем наш хост 192.168.56.11 по порту 10050

Пробуем пингануть
!["Zabbix"](./images/1.png)

Добавляем темплейт метрик

!["Zabbix"](./images/2.png)

Проверяем метрики

!["Zabbix"](./images/3.png)

Добавляем триггер 

!["Zabbix"](./images/4.png)

!["Zabbix"](./images/5.png)

Можем также персонализировать дашборд

!["Zabbix"](./images/6.png)

## Контрольные вопросы

1.  Zabbix-server собирает даныне с агентов и обрабатывает триггеры
    
Zabbix-agent занимается мониторингом метрик на конкретной машине
    
Zabbix-web это простой веб интерфейс для отображения метрик

2. Данные идут от агентов к серверу и дальше веб интерфейс получает с сервера необходимые метрики

3. Trigger это условие при выполнении которого буде послан оповестительный сигнал

Item эта отдельная метрика которую может проверять триггер