# Лабораторная 5

### Выполнение

Создадим виртуальную машину при помощи vagrant и запустим на ней в контейнере гитлаб 

```bash
Vagrant.configure("2") do |config|

  config.vm.box = "ubuntu/jammy64"
  config.vm.provider "virtualbox" do |vb|
    vb.memory = 4096 
    vb.cpus = 2
  end

  config.vm.define "gitlab-vm" do |vm1|
    vm1.vm.hostname = "gitlab-vm"
    vm1.vm.network "private_network", ip: "192.168.56.10"

    vm1.vm.provision "shell", inline: <<-SHELL
      sudo apt update -y
      sudo apt install -y docker.io

      sudo docker run -d \
        --hostname 192.168.100.75 \
        -p 80:80 \
        -p 443:443 \
        -p 8022:22 \
        --name gitlab \
        -e GITLAB_OMNIBUS_CONFIG="external_url='http://192.168.56.10'; gitlab_rails['gitlab_shell_ssh_port']=8022" \
        -v gitlab-data:/var/opt/gitlab \
        -v ~/gitlab-config:/etc/gitlab \
        gitlab/gitlab-ce:latest
      SHELL
  end
  
end
```

```bash
vagrant up
vagrant ssh gitlab-vm
docker logs -f gitlab
```

Ждём пока gitlab запустится и заходим по ip 192.168.56.10 и смотрим root пароль

![gitlab](./images/1.png)

```bash
sudo docker exec -it gitlab cat /etc/gitlab/initial_root_password
```

![gitlab](./images/2.png)
![gitlab](./images/3.png)

Установка раннера на виртуальной машине

```bash
curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash
```

Wait 20 minutes until it sets up

```bash
sudo apt-get install -y gitlab-runner
```

Переходим в ```Admin Area > CI/CD > Runners > New instance runner```

![gitlab](./images/4.png)

![gitlab](./images/5.png)

Регистрируем раннер

```bash
sudo gitlab-runner register --non-interactive \
  --url "http://192.168.56.10" \
  --registration-token "glrt-2n5Wu1oIODnnAD-f_Su9H286MQp0OjEKdToxCw.01.1212deqj6" \
  --executor "docker" \
  --docker-image "php:8.2-cli" \
  --description "laravel-runner" \
  --tag-list "laravel,php" \
  --run-untagged="true" \
  --locked="false"
```

И запускаем его

```bash
gitlab-runner run
sudo gitlab-runner status
```

![gitlab](./images/6.png)

Создаём проект

![gitlab](./images/7.png)

Клонируем репозиторий наш репозиторий и репозиторий с laravel преоктом

```bash
git clone http://192.168.56.10/root/lab5.git
git clone https://github.com/laravel/laravel
cd lab5
```

Копируем содержимое в наш репозиторий и создаём Dockerfile, .env.testing 

```dockerfile
# Используем официальный образ PHP с Apache
FROM php:8.2-apache

# Устанавливаем зависимости
RUN apt-get update && apt-get install -y \
    libpng-dev libonig-dev libxml2-dev \
    && docker-php-ext-install pdo_mysql mbstring exif pcntl bcmath

# Устанавливаем Composer
COPY --from=composer:latest /usr/bin/composer /usr/bin/composer

# Копируем код приложения
COPY . /var/www/html
RUN composer install --no-scripts --no-interaction
RUN chown -R www-data:www-data /var/www/html/storage /var/www/html/bootstrap/cache
RUN chmod -R 775 /var/www/html/storage

# Настраиваем Apache
RUN a2enmod rewrite
EXPOSE 80

CMD ["apache2-foreground"]
```

```env
APP_NAME=Laravel
APP_ENV=testing
APP_KEY=
APP_DEBUG=true
APP_URL=http://localhost
APP_LOCALE=en
APP_FALLBACK_LOCALE=en
APP_FAKER_LOCALE=en_US
APP_MAINTENANCE_DRIVER=file
# APP_MAINTENANCE_STORE=database
PHP_CLI_SERVER_WORKERS=4
BCRYPT_ROUNDS=12
LOG_CHANNEL=stack
LOG_STACK=single
LOG_DEPRECATIONS_CHANNEL=null
LOG_LEVEL=debug
DB_CONNECTION=mysql
DB_HOST=mysql
DB_PORT=3306
DB_DATABASE=laravel_test
DB_USERNAME=root
DB_PASSWORD=root
SESSION_DRIVER=database
SESSION_LIFETIME=120
SESSION_ENCRYPT=false
SESSION_PATH=/
SESSION_DOMAIN=null
BROADCAST_CONNECTION=log
FILESYSTEM_DISK=local
QUEUE_CONNECTION=database
CACHE_STORE=database
# CACHE_PREFIX=
MEMCACHED_HOST=127.0.0.1
REDIS_CLIENT=phpredis
REDIS_HOST=127.0.0.1
REDIS_PASSWORD=null
REDIS_PORT=6379
MAIL_MAILER=log
MAIL_SCHEME=null
MAIL_HOST=127.0.0.1
MAIL_PORT=2525
MAIL_USERNAME=null
MAIL_PASSWORD=null
MAIL_FROM_ADDRESS="hello@example.com"
MAIL_FROM_NAME="${APP_NAME}"
```

Создадим .gitlab-ci.yaml

```yaml
stages:
	  - test
	  - build
	services:
	  - mysql:8.0
	variables:
	  MYSQL_DATABASE: laravel_test
	  MYSQL_ROOT_PASSWORD: root
	  DB_HOST: mysql
	test:
	  stage: test
	  image: php:8.2-cli
	  before_script:
	    - apt-get update -yqq
	    - apt-get install -yqq libpng-dev libonig-dev libxml2-dev libzip-dev unzip git
	    - docker-php-ext-install pdo_mysql mbstring exif pcntl bcmath
	    - curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer
	    - composer install --no-scripts --no-interaction
	    - cp .env.testing .env
	    - php artisan key:generate
	    - php artisan migrate --seed
	    - cp .env .env.testing
	    - php artisan config:clear
	  script:
	    - vendor/bin/phpunit
	  after_script:
	    - rm -f .env
```

Коммитим и пушим

```bash
git add .
git commit -m "Addedl laravel app with CI/CD config"
git push
```

![gitlab](./images/8.png)
