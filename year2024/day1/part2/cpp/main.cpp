#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
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
    std::map<int, int> right_numbers;

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
        if( right_numbers.contains(number) )
        {
            right_numbers[number]++;
        }
        else
        {
            right_numbers[number] = 1;
        }
    }

    for(const auto number : left_numbers)
    {
        if(const auto res = right_numbers.find(number); res != right_numbers.end())
        {
            sum += number * res->second;
        }
    }

    std::cout << "Solution: " << sum << std::endl;
    return 0;
}
