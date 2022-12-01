#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

unsigned int convert_2_decimal(const std::string& bits) {
    unsigned int position = 0;
    unsigned int sum = 0;
    for(auto it = bits.rbegin(); it != bits.rend(); it++) {
        if (*it == '1') {
            sum += static_cast<unsigned int>(std::pow(2, position));
        }
        position++;
    }
    return sum;
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> binaries;
    while (std::getline(input_data, line)) {
        binaries.push_back(line);
    }
    input_data.close();

    auto count_bits = (*binaries.begin()).size();
    std::string gamma;
    std::string epsilon;

    for(std::size_t b = 0; b < count_bits; b++) {
        auto count_0 = 0;
        auto count_1 = 0;
        for(const auto & binary : binaries) {
            if(binary[b] == '0') {
                count_0++;
            } else {
                count_1++;
            }
        }
        gamma.push_back((count_1 > count_0) ? '1' : 0);
        epsilon.push_back((count_1 > count_0) ? '0' : '1');
    }

    unsigned int gamma_value = convert_2_decimal(gamma);
    unsigned int epsilon_value = convert_2_decimal(epsilon);

    std::cout << "The solution is: " << gamma_value * epsilon_value << std::endl;
    return 0;
}
