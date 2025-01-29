#!/bin/bash

# enter folder path and pattern
echo "Enter the folder path:"
read folder
echo "Enter the search pattern:"
read pattern

# Check if the folder exists
if [ ! -d "$folder" ]; then
    echo "The folder does not exist."
    exit 1
fi

# search for files containing the pattern
echo "Files containing the pattern '$pattern':"
grep -rl  "$pattern" "$folder" 

