#!/bin/sh
# (if) mkdir build && cd build
rm -r *
cmake ..
cmake --build .