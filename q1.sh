#!/bin/bash

if [ $# -eq 0 ]; then
    echo "No file specified"
    exit 1
fi

cp "$1" "$1_copy"
echo "Duplicate copy of $1 created as $1_copy"
