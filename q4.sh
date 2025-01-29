#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <option> <file>"
    exit 1
fi

option=$1
file=$2

case $option in
    -linecount ) wc -l "$file";;
    -wordcount ) wc -w "$file";;
    -charcount ) wc -c "$file";;
    * ) echo "Invalid option";;
esac
