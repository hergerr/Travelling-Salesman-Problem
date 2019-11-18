#!/bin/bash

while [ 1 ]; do
    free | grep Mem >> "${1}_dp.txt"
done
