#!/bin/sh
set -e  

sleep 30

mysql -h sql -u root -prootpassword post_db --skip-ssl < /var/www/html/sql/seed.sql

exec apache2-foreground