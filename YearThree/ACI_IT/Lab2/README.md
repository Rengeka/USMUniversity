# Лабораторная 2 (Создание Shell скриптов)

## Задание 1 (CLI-ассистент)

Создадим cli_assistant.sh файл и установим shebang 

Добавим переменные, которые потребуются нам для выполнения условий задания 

    MAX_TRIES - максимальное количество попыток пользовательского ввода 
    TRIES - текущее количество потраченных попыток
    NAME - переменная для имени пользователя
    GROUP - переменная для группы пользователя

```sh
#!/bin/bash
MAX_TRIES=3
TRIES=0
NAME=""
GROUP=""
```

Выводим приметствие на экран и даём три попытки ввести имя

```sh
echo "Greetings! I am your personal CLI assistant."

while [ -z "$NAME" ] && [ $TRIES -lt $MAX_TRIES ]; do
    echo "Please, write your name:"
    read NAME

    if [ -z "$NAME" ]; then
        TRIES=$((TRIES+1))
        if [ $TRIES -lt $MAX_TRIES ]; then
            echo "You didn't type anything. Please try again ($TRIES/$MAX_TRIES)."
        fi
    fi
done
```

Обрабатываем ошибку (Есил пользователь потртил все попытки) и возвращаем exit code 1
```sh
if [ -z "$NAME" ]; then
    echo "Too many failed attempts. Goodbye!"
    exit 1
fi
```

Аналогично поступаем и с группой 
```sh

while [ -z "$GROUP" ] && [ $TRIES -lt $MAX_TRIES ]; do
    echo "Please, write your group:"
    read GROUP

    if [ -z "$GROUP" ]; then
        TRIES=$((TRIES+1))
        if [ $TRIES -lt $MAX_TRIES ]; then
            echo "You didn't type anything. Please try again ($TRIES/$MAX_TRIES)."
        fi
    fi
done

if [ -z "$NAME" ]; then
    echo "Too many failed attempts. Goodbye!"
    exit 1
fi
```

Если пользователь успешно ввёл свои данные, выводим ему небольшую информационную сводку
```sh
echo "Date: $(date) "
echo "Uptime: $(uptime)"
echo "Space: $(df -h / | awk 'NR==2 {print $4}')"
echo "Users: $(who | wc -l)"

echo "Nice to meet you $NAME from $GROUP!"
```

## Задание 2 (Резервное копирование каталога с логированием и ротацией)

Создадим backup_rot.sh файл

Создадим две переменные и запишем в них аргументы скрипта

    SOURCE - Источник (То, что мы будем бэкапить)
    BACKUP - Папка куда сохранять бэкап

```sh
#!/bin/bash

SOURCE=$1
BACKUP=$2
```

Проверим аргументы и выбрасим error code 1 если первый аргумент отстутсвует и error code 2 если папку SOURCE не существует
```sh
if [ -z $SOURCE ]; then
    echo "Error: not path to source direcotry was provided"
    echo "Usage: $0 <source directory> [<backup direcotry>]"
    exit 1
fi

if [ ! -d "$SOURCE" ]; then
    echo "Error: Source '$SOURCE' does not exist or is not a directory."
    exit 2
fi
```

Если директория BASCKUP не была передана, зададим значение по умолчанию, если была передана то проверим её наличие и разрешение для записи (в противном случае возвращаем error code 3)
```sh
if [ -z $BACKUP ]; then
    $BACKUP="~/backups"
fi

mkdir -p "$BACKUP"
if [ ! -w "$BACKUP" ]; then
    echo "Error: Backup directory '$BACKUP' is not writable."
    exit 3
fi
```

Архивируем данные и проверяем код, выполнения
```sh
BASENAME=$(basename "$SOURCE")
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
ARCHIVE="backup_${BASENAME}_${TIMESTAMP}.tar.gz"
ARCHIVE_PATH="$BACKUP/$ARCHIVE"

tar -czf "$ARCHIVE_PATH" -C "$(dirname "$SOURCE")" "$BASENAME"
STATUS=$?

if [ $STATUS -eq 0 ]; then
    SIZE=$(du -h "$ARCHIVE_PATH" | cut -f1)
else
    SIZE=0
fi
```

Логаем и дполонительно удаляем старые бэкапы если превышен лимит
```sh
LOGFILE="$BACKUP/backup.log"
echo "$(date -Iseconds) SRC=$SOURCE DST=$BACKUP FILE=$ARCHIVE SIZE=$SIZE STATUS=$STATUS" >> "$LOGFILE"

if [ -n "$MAX_BACKUPS" ] && [ "$MAX_BACKUPS" -gt 0 ]; then
    COUNT=$(ls -1 "$BACKUP"/backup_"$BASENAME"_*.tar.gz 2>/dev/null | wc -l)
    if [ "$COUNT" -gt "$MAX_BACKUPS" ]; then
        ls -1t "$DST"/backup_"$BASENAME"_*.tar.gz | tail -n +"$((MAX_BACKUPS+1))" | while read f; do
            rm -f "$f"
        done
    fi
fi

exit $STATUS
```

## Задание 3 (Мониторинг дискового пространства)

Создадим disk_monitor.sh

Создадим переменные, котоыре будут принимать значения аргументов и установим значения по умолчанию 

    TARGET - путь к файловой системы ('\' по умолчанию)
    ThRESHOLD - порог заполненности (80% по умолчанию)

```sh
#!/bin/bash

TARGET="${1:-/}"
THRESHOLD="${2:-80}"
```

Проверим что путь существует
```sh
if [ ! -e "$TARGET" ]; then
    echo "Error: Path '$TARGET' does not exist."
    exit 2
fi
```

Получим процент использования и проверим его
```sh
USAGE=$(df -h "$TARGET" 2>/dev/null | awk 'NR==2 {print $5}' | tr -d '%')

if [ -z "$USAGE" ]; then
    echo "Error: Unable to get disk usage for '$TARGET'."
    exit 2
fi
```

Порлучим текущую дату и проверим процент заполненности диска
```sh
NOW=$(date '+%Y-%m-%d %H:%M:%S')

if [ "$USAGE" -lt "$THRESHOLD" ]; then
    STATUS="OK"
    EXIT_CODE=0
else
    STATUS="WARNING: disk is nearly full!"
    EXIT_CODE=1
fi
```

Если всё в норме, выведем информацию
```sh
echo "$NOW"
echo "Path: $TARGET"
echo "Usage: $USAGE%"
echo "Status: $STATUS"

exit $EXIT_CODE
```