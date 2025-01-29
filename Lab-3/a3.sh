#!/bin/bash

if [ -z "$1" ]; then
  echo "Please provide a file name as an argument"
  exit 1
fi

filename=$1

awk 'NR % 2 == 0 {print > "evenfile"} NR % 2 == 1 {print > "oddfile"}' "$filename"

