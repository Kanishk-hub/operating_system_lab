#!/bin/bash

# Prompt user for the file name
echo "Enter the filename:"
read filename

# Check if the file exists
if [ ! -f "$filename" ]; then
    echo "The file does not exist."
    exit 1
fi

# Use awk to delete even-numbered lines
awk 'NR % 2 != 0' "$filename" > temp_file && mv temp_file "$filename"

echo "Even-numbered lines have been deleted in $filename."

