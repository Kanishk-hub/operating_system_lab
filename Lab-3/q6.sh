#!/bin/bash

# Loop through all files in the current directory
for file in *; do
    # Check if the item is a regular file
    if [ -f "$file" ]; then
        # Use sed to replace "ex:" with "Example:" only at the beginning of the line or after a period
        sed -i -E 's/(^|\.)\s*ex:/\1 Example:/g' "$file"
        echo "Modified file: $file"
    fi
done

