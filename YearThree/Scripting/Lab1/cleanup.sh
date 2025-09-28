#!/bin/bash

#Task (2)

#Cleaning up temporary files:
#   The script should be named cleanup.sh;
#   The script should take at least one argument: the path to the directory to clean up;
#   The remaining arguments are optional and specify the types of files to delete (e.g., .tmp, .log);
#   By default, files with the .tmp extension are deleted;
#   At the end of the script execution, it should output the number of deleted files;
#   The script should check that the specified directory exists and output appropriate error messages.

if [ -z "$1" ]; then
    echo "Error: not path to direcotry was provided"
    echo "Usage: $0 <directory> [arg1 arg2 ...]"
    exit 1
fi

DIR="$1"
shift  

if [ ! -d "$DIR" ]; then
    echo "Error: Directory '$DIR' not found on the provided path"
    exit 1
fi

if [ $# -eq 0 ]; then
    FILE_TYPES=("*.tmp")
else
    FILE_TYPES=()
    for ext in "$@"; do
        FILE_TYPES+=("*$ext")
    done
fi

deleted_count=0

echo "Cleaning was started"

for pattern in "${FILE_TYPES[@]}"; do
    files=( "$DIR"/$pattern )
    for f in "${files[@]}"; do
        if [ -f "$f" ]; then
            rm "$f"
            ((deleted_count++))
        fi
    done
done

echo "Cleaning was finished. Totally deleted $deleted_count files "