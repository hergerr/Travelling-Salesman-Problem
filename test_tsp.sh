#/bin/bash
cd /home/tymek/dev/C++/Travelling-Salesman/cmake-build-debug/

for i in 10 11 12 13 14 15 16 17 18
do
  echo data${i}.txt
  ./Travelling_Salesman <<< "4 data${i}.txt 3 0"
done

