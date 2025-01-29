#!/bin/bash

if [ $# -eq 0 ]; then
    echo "No strings specified"
    exit 1
fi

function sort_strings {
    for i in "$@"; do
        echo "$i"
    done | sort
}

sorted_strings=$(sort_strings "$@")
echo "$sorted_strings"
