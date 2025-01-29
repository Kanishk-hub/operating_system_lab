#!/bin/bash

echo "Enter value of n"
read n

for((i=0; i<n; i++)); do
  if (( i % 2 == 0 )) ; then
  echo -n $i
  fi
  done
  echo