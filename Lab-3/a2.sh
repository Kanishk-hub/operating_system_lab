#!/bin/bash

read -p "Enter a number: " num

factorial=1

for (( i=2; i<=num; i++ )); do
  factorial=$((factorial * i))
done

echo "Factorial of $num is $factorial"
