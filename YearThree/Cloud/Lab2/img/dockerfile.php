FROM php:8.2-apache

COPY PHP/ /var/www/html/
COPY apache.conf /etc/apache2/sites-enabled/000-default.conf

RUN apt-get update && apt-get install -y default-mysql-client \
    && docker-php-ext-install pdo pdo_mysql
    
EXPOSE 80