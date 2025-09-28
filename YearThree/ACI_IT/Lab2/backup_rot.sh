#!/bin/bash

SOURCE=$1
BACKUP=$2

if [ -z $SOURCE ]; then
    echo "Error: not path to source direcotry was provided"
    echo "Usage: $0 <source directory> [<backup direcotry>]"
    exit 1
fi

if [ ! -d "$SOURCE" ]; then
    echo "Error: Source '$SOURCE' does not exist or is not a directory."
    exit 2
fi


if [ -z $BACKUP ]; then
    $BACKUP="~/backups"
fi

mkdir -p "$BACKUP"
if [ ! -w "$BACKUP" ]; then
    echo "Error: Backup directory '$BACKUP' is not writable."
    exit 3
fi

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