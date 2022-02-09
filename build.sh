#!/bin/bash

rm -rf output
rm -rf build

mkdir output
mkdir build

gcc -c src/a.c -o output/a.c.o -fPIC
ar -rcs output/liba.a output/a.c.o

gcc -c src/b.c -o output/b.c.o -fPIC
ar -rcs output/libb.a output/b.c.o

cd build
cmake ..
make