FROM php:8.2-apache

COPY PHP/ /var/www/html/
COPY apache.conf /etc/apache2/sites-enabled/000-default.conf
COPY startup.sh /usr/local/bin/

RUN apt-get update && apt-get install -y default-mysql-client \
    && docker-php-ext-install pdo pdo_mysql \
    && chmod +x /usr/local/bin/startup.sh
    
EXPOSE 80

CMD ["/usr/local/bin/startup.sh"]