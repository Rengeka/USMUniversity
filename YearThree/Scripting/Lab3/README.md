# Lab 3

### Project structure

cron directory contains dockerfile, cronjob, currency_exchange_rate.py startup.sh scripts

    cronjob is a config file with cron events. It is a pruduction file. If you want to test cron, just copy testing cron events form cronjob.test

    currency_exchange_rate.py is a script from lab2, that makes call to api and gets exchange data

    startup.sh is an entrypoint script that creates log files and runs cron

    dockerfile is building the docker image with all of the files above, downloads dependencies and rusn entrypoint.sh

php direcotry is a directory with exchange api, that returns exchange data called from .py script

docker-compose.yaml runs two containers. One with cron, another with php api

run.ps1 is a simple script to start application

### Starting the app

Run ```./run.ps1```

### Verifying 

To verify if cron is working correctly you may run cron with testing events from cronjob.test

Verify .log file via ```cat /var/log/cron.log.```

