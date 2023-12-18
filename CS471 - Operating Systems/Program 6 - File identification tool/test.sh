#!/bin/bash

# Array of files to check
files=("sda1.out" "sda2.out" "sda3.out" "sda4.out" "sda5.out" "sda6.out" "sda7.out" "sdb1.out")

make myfile
echo ""

# Loop through each file and run the program
for file in "${files[@]}"
do
  echo "jtroyer@brooks:~/CS474/program6> ./myfile "$file""
  ./myfile "$file"
  echo " "
  echo " "
done
