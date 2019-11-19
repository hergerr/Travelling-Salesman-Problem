#!/bin/bash

cd cmake-build-debug/

for i in 10
do
  ./Travelling_Salesman <<< "4 data${i}.txt 1 0" 
done