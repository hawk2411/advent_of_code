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

    std::vector<int> left_numbers;
    std::vector<int> right_numbers;

    std::string text_line;
    while(std::getline(input_data, text_line)) {
        string_trimmer::trim(text_line);
        if(text_line.empty()) {
            break;
        }
        std::size_t pos{0};
        auto number = std::stoi(text_line, &pos);
        left_numbers.push_back(number);

        auto secondString = string_functions::trim(text_line.substr(pos));
        number = std::stoi(secondString, &pos);
        right_numbers.push_back(number);
    }
    std::ranges::sort(left_numbers);
    std::ranges::sort(right_numbers);
    for( auto i = 0; i < left_numbers.size(); i++)
    {
        sum += std::abs(right_numbers[i] - left_numbers[i]);
    }
    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


