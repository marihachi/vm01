#!/bin/bash

cmake -S src -B build
ret=$?

if [ $ret -eq 0 ]; then
    cd ./build
    ret=$?

    if [ $ret -eq 0 ]; then
        make
    fi
fi
