#!/bin/bash
MAX_TRIES=3
TRIES=0
NAME=""
GROUP=""

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

if [ -z "$NAME" ]; then
    echo "Too many failed attempts. Goodbye!"
    exit 1
fi

echo "Hello $NAME! Please type here your group:"
read GROUP

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

echo "Date: $(date) "
echo "Uptime: $(uptime)"
echo "Space: $(df -h / | awk 'NR==2 {print $4}')"
echo "Users: $(who | wc -l)"

echo "Nice to meet you $NAME from $GROUP!"