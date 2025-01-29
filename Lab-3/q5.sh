#!/bin/bash

# Enter file extension and target folder
echo "Enter the file extension (e.g., .txt, .text):"
read extension
echo "Enter the target folder:"
read target_folder

# Check if the target folder exists, if not create it
if [ ! -d "$target_folder" ]; then
    mkdir "$target_folder"
fi

# Copy files with the specified extension (single level, no subdirectories)
for file in *$extension; do
    if [ -f "$file" ]; then
        cp "$file" "$target_folder/"
    fi
done

echo "Files with extension $extension have been copied to $target_folder."

