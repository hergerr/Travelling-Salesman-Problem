#!/bin/bash

while [ 1 ]; do
    free | grep Mem >> "${1}.txt"
    sleep 0.1
done
