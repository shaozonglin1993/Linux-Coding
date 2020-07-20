#!/bin/bash

max=0
min=0
count=0
sum=0
while read line
do
	if [ $count -eq 0 ];then
	max=$line
	min=$line
	let count++
	let sum+=$line
	continue
	fi
	[ "$max" -lt "$line" ] && max=$line
	[ "$min" -gt "$line" ] && min=$line
	let sum+=$line
	let count++
done<file

echo $max
echo $min
echo "ibase=10; scale=2; $sum/$count" | bc
