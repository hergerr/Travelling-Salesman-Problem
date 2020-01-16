#!/bin/bash
set -e

echo "file name    result    expected"

for i in 10 11 12 13 14 15 16 17 18 21 24 26 29 42 58 120
do
  cd cmake-build-debug/
  echo -ne "data${i}: \t" && ./Travelling_Salesman <<< "4 data${i}.txt 9 0" | grep Result | awk {'printf $2'} && echo -ne '\t' && grep -w "data${i}" opt.txt | awk {'print $3'}
  cd ..
done