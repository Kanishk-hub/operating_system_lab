#!/bin/bash

if [ $# -eq 0 ]; then
    echo "No files specified"
    exit 1
fi

for file in "$@"; do
    if [ -f "$file" ]; then
        read -p "Do you want to remove $file? (y/n) " answer
        case $answer in
            [Yy]* ) rm "$file"; echo "$file removed";;
            [Nn]* ) echo "$file not removed";;
            * ) echo "Invalid input";;
        esac
    else
        echo "$file does not exist"
    fi
done
