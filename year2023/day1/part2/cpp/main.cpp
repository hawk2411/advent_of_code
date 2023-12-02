#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include <trim_functions.h>
constexpr auto COUNT_DIGITS = 9;
const std::array<std::string_view, COUNT_DIGITS*2> allow_digits = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

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

        std::size_t smallest_pos = text_line.size();
        for(auto i = 0; i < allow_digits.size(); ++i) {
            auto pos = text_line.find(allow_digits[i]);
            if(pos == std::string::npos) {
                continue;
            }
            if(pos > smallest_pos ) {
                continue;
            }

            if( smallest_pos == 0 ) {
                break; //can't be better
            }
            smallest_pos = pos;
            int digit = (i >= COUNT_DIGITS)? i - COUNT_DIGITS : i;
            digit++;
            left = '0' + digit;
        }

        std::size_t greatest_pos = 0;
        for(auto i = 0; i < allow_digits.size(); ++i) {
            const auto pos = text_line.rfind(allow_digits[i]);
            if(pos == std::string::npos) {
                continue;
            }
            if(pos < greatest_pos ) {
                continue;
            }

            greatest_pos = pos;
            int digit = (i >= COUNT_DIGITS)? i - COUNT_DIGITS : i;
            digit++;
            right = '0' + digit;
        }

        std::string digit = {left, right};
        char *error_break;;
        auto result = std::strtol(digit.c_str(), &error_break, 10);
        sum += result;
    }

    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


