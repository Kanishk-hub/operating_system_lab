#!/bin/bash

# Prompt user to enter basic salary and TA
echo "Enter Basic Salary:"
read basics
echo "Enter TA:"
read ta

# Calculate the gross salary
gross_salary=$(echo "$basics + $ta + 0.1 * $basics" | bc -l)

# Display the gross salary
echo "Gross Salary: $gross_salary"

