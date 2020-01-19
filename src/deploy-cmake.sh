#!/bin/bash
mv build/*.sh .
rm -rf build
mkdir build
cp *.sh build/
cd build
cmake -DCOMPONENT=ALL -DNAL=ALL -DTPM=ON ../
cd ..

