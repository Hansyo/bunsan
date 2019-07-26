#!/bin/bash
for((i=1;i <= 128;i++));do
RESULT="0"
F_NAME=`echo "result_mat_mul_base.phi_$i.txt"`
for line in `cat $F_NAME`;do
RESULT=`echo "$RESULT + $line" | bc`
done
RESULT=`echo "scale=6; $RESULT / 10" | bc`
echo "$i $RESULT"
echo "$i $RESULT" >> result_all.txt
done
