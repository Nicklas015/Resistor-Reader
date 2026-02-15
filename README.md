# Version 1.2

# Resistor-Reader
This project aim to make a smart reader of resistor components. 

# how to build and see results with cross compiling 
rm -rf build
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=toolchains/rpi-zero.cmake
cmake --build build -j$(nproc)

scp build/resistor-reader pi@192.168.0.152:~/

# use calculation for color determination 
 mkdir -p ./cpp_test/build && g++ -std=c++17 -Wall -g cpp_test/calculator.cpp -o ./cpp_test/build/calculator && ./cpp_test/build/calculator 