#!/bin/bash
set -e

for i in 17 18 21
do
  ./measure_memory.sh "data${i}" &
  cd cmake-build-debug/
  ./Travelling_Salesman <<< "4 data${i}.txt 3 0"
  process_id=`/bin/ps -fu $USER| grep "measure" | grep -v "grep" | awk '{print $2}'`
  echo "$process_id"
  sleep 1
  kill $process_id
  cd ..
done

