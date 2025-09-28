#!/bin/bash

TARGET="${1:-/}"
THRESHOLD="${2:-80}"

if [ ! -e "$TARGET" ]; then
    echo "Error: Path '$TARGET' does not exist."
    exit 2
fi

USAGE=$(df -h "$TARGET" 2>/dev/null | awk 'NR==2 {print $5}' | tr -d '%')

if [ -z "$USAGE" ]; then
    echo "Error: Unable to get disk usage for '$TARGET'."
    exit 2
fi

NOW=$(date '+%Y-%m-%d %H:%M:%S')

if [ "$USAGE" -lt "$THRESHOLD" ]; then
    STATUS="OK"
    EXIT_CODE=0
else
    STATUS="WARNING: disk is nearly full!"
    EXIT_CODE=1
fi

echo "$NOW"
echo "Path: $TARGET"
echo "Usage: $USAGE%"
echo "Status: $STATUS"

exit $EXIT_CODE