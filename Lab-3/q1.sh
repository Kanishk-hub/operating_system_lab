#!/bin/bash

if [ -d "$1" ]; then
  echo "$1 is a directory"
elif [ -f "$1" ]; then
  echo "$1 is a regular file"
else
  echo "$1 is not a valid file or directory"
fi

