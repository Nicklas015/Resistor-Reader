# Version 1

# Resistor-Reader
This project aim to make a smart reader of resistor components. 

# how to build and see results 
cmake --build build && ./build/color_reader

# use calculation
 mkdir -p ./cpp_test/build && g++ -std=c++17 -Wall -g cpp_test/calculator.cpp -o ./cpp_test/build/calculator && ./cpp_test/build/calculator 