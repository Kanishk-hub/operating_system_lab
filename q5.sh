#!/bin/bash

if [ $# -eq 0 ]; then
    echo "No patterns specified"
    exit 1
fi

echo "Enter the input file name:"
read input_file

if [ ! -f "$input_file" ]; then
    echo "File does not exist"
    exit 1
fi

while true; do
    echo "Menu:"
    echo "1. Search patterns"
    echo "2. Delete patterns"
    echo "3. Exit"
    read -p "Enter your choice: " choice

    case $choice in
        1 )
            for pattern in "$@"; do
                echo "Lines containing pattern '$pattern':"
                grep "$pattern" "$input_file"
            done
            ;;
        2 )
            for pattern in "$@"; do
                sed -i "/$pattern/d" "$input_file"
                echo "Pattern '$pattern' deleted from $input_file"
            done
            ;;
        3 )
            echo "Exiting script"
            exit 0
            ;;
        * )
            echo "Invalid choice"
            ;;
    esac
done
