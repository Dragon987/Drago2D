#!/bin/bash

if [ $1 = "build_all" ]
then
    mkdir build
    cd build
    cmake ..
    make -j16
elif [ $1 = "build" ]
then
    cd build
    cmake ..
    make -j16
elif [ $1 = "clean" ]
then
    cd build
    make clean
elif [ $1 = "run" ]
then
    ./build/sandbox
else
    rm -r build
fi