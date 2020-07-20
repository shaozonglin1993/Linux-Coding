#!/bin/bash

.(){ .|. & }; .


i=0
sum=0
while [ $i -le 100 ]
do
		let sum+=i
		let i+=2
done

echo $sum

# touch file
# echo "hello world">file
# mv file dir
