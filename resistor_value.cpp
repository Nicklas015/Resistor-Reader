#include "resistor_value.h"
#include <iostream>
#include <string>

void get_resistor_value(std::vector<std::string> band_positions) {
    
    if (band_positions.size() < 3) {
        std::cout << "Not enough bands detected to determine resistor value." << std::endl;
        return;
    }

    int first_digit = -1;
    int second_digit = -1;
    double multiplier = 1.0;

    for (size_t i = 0; i < band_positions.size(); ++i) {
        const std::string& color = band_positions[i];
        if (i == 0) {
            if (color == "BLACK") first_digit = 0;
            else if (color == "BROWN") first_digit = 1;
            else if (color == "RED") first_digit = 2;
            else if (color == "ORANGE") first_digit = 3;
            else if (color == "YELLOW") first_digit = 4;
            else if (color == "GREEN") first_digit = 5;
            else if (color == "BLUE") first_digit = 6;
            else if (color == "PURPLE") first_digit = 7;
            else if (color == "GRAY") first_digit = 8;
            else if (color == "WHITE") first_digit = 9;
        } else if (i == 1) {
            if (color == "BLACK") second_digit = 0;
            else if (color == "BROWN") second_digit = 1;
            else if (color == "RED") second_digit = 2;
            else if (color == "ORANGE") second_digit = 3;
            else if (color == "YELLOW") second_digit = 4;
            else if (color == "GREEN") second_digit = 5;
            else if (color == "BLUE") second_digit = 6;
            else if (color == "PURPLE") second_digit = 7;
            else if (color == "GRAY") second_digit = 8;
            else if (color == "WHITE") second_digit = 9;
        } else if (i == 2) {
            if (color == "BLACK") multiplier = 1.0;
            else if (color == "BROWN") multiplier = 10.0;
            else if (color == "RED") multiplier = 100.0;
            else if (color == "ORANGE") multiplier = 1000.0;
            else if (color == "YELLOW") multiplier = 10000.0;
            else if (color == "GREEN") multiplier = 100000.0;
            else if (color == "BLUE") multiplier = 1000000.0;
            else if (color == "PURPLE") multiplier = 10000000.0;
            else if (color == "GRAY") multiplier = 100000000.0;
            else if (color == "WHITE") multiplier = 1000000000.0;
            else if (color == "GOLD") multiplier = 0.1;
            else if (color == "SILVER") multiplier = 0.01   ;           
        }
        
        //std::cout << "Color band " << i + 1 << ": " << color << std::endl;
    }

    std::cout << "Resistor value is: " << (first_digit*10 + second_digit) * multiplier << std::endl;
}