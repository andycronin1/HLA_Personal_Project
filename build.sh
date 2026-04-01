#!/bin/zsh
# Full rebuild: only needed when CMakeLists.txt changes.
# For regular code changes, run: cd build && make
rm -rf build
mkdir build
cd build
cmake ..
cmake --build . --config Release
cd ..
cd bin