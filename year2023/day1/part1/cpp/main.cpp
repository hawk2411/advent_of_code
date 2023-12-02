#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <trim_functions.h>

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    long sum  = 0;

    std::string text_line;
    while(std::getline(input_data, text_line)) {
        string_trimmer::trim(text_line);
        if(text_line.empty()) {
            break;
        }

        char left = '\0';
        char right = '\0';

        for(const auto c : text_line) {
            if(isdigit(c)) {
                left = c;
                break;
            }
        }
        auto last = text_line.rbegin();
        while ( last != text_line.rend()) {
            if(isdigit(*last)){
                right = *last;
                break;
            }
            last++;
        }
        std::string digit = {left, right};
        char *error_break;;
        auto result = std::strtol(digit.c_str(), &error_break, 10);
        sum += result;
    }

    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


