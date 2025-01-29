#!/bin/bash

# Use find to search for .txt files and rename them to .text
find . -type f -name "*.txt" | while read file; do
    # Replace .txt with .text
    mv "$file" "${file%.txt}.text"
done

