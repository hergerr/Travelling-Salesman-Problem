#!/bin/bash
set -e

for i in 10 11 12 13 14 15 16 17 18 21 24 26 29 42 58 120
do
#  ./measure_memory_dp.sh "data${i}" &
#  sleep 0.2
  cd cmake-build-debug/
  ./Travelling_Salesman <<< "4 data${i}.txt 10 0"
#  process_id=`/bin/ps -fu $USER| grep "measure" | grep -v "grep" | awk '{print $2}'`
#  sleep 0.2
#  kill $process_id
  cd ..
done