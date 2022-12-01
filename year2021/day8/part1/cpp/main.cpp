#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <map>
#include "input_parser.h"


int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    std::string text_line;

    unsigned int sum = 0;

    while(std::getline(input_data, text_line)) {
        auto count_unique_sequences = input_parser::get_number(text_line);
        sum += count_unique_sequences;
    }

    input_data.close();


    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


