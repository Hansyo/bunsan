#!/bin/bash

for ((i=1; i <= 128;i++));do
	for ((j=1; j <= 5;j++));do
		./$1 $i >> result/result_$1_$i.txt
		tail -n 1 result/result_$1_$i.txt
	done
done
