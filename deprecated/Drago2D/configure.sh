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
else
    rm -r build
fi