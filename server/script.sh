#!/bin/sh
cd build
rm -r *
cmake ..
cmake --build .
