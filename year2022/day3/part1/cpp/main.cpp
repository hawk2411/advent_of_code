#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int getPriority(const char &item) {

    // 27 -  52
    // A = 65 - 38  == 27
    // 1 - 26
    // a = 97 - 96 == 1

    return std::isupper(item) ? item - 38 : item - 96;
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    unsigned int sum = 0u;
    std::string text_line;
    while(std::getline(input_data, text_line)) {
        std::size_t half_size = text_line.size() / 2;
        auto first_compartment = text_line.substr(0, half_size);
        auto second_compartment = text_line.substr(half_size);

        for(const auto& c : first_compartment) {
            auto pos = second_compartment.find(c);
            if(pos == std::string::npos) {
                continue;
            }
            //here we found something in both compartment
            int priority = getPriority(c);
            sum += priority;
            break;
        }
    }
    input_data.close();


    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


