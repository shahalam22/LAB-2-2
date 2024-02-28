#!/bin/bash

target="/home/shahalamabir/Desktop/LAB-2-2"

files=$(find "$target" -type f -name "*.c" -o -name "*.cpp")

for a in $files; do
	name=$(basename "$a")
	size=$(du --bytes "$a" | cut -f1)
	loc=$(wc -l < "$a")
	echo "Name - $name Size - $size LOC - $loc"
done