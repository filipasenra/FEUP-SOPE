#!/bin/bash
name=$1
rm ./$name --force
cc $name.c -o $name >/dev/null 2>&1
rc=$?
if [ $rc -ne 0 ]; # $rc not equal to zero
then
echo COMPILATION ERROR!
else
./$name $2 $3
fi