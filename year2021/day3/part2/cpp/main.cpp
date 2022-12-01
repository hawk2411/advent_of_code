#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <numeric>
#include <algorithm>

unsigned int convert_2_decimal(const std::string &bits) {
    unsigned int position = 0;
    unsigned int sum = 0;

    sum = std::accumulate(bits.rbegin(), bits.rend(), sum, [&position](unsigned sum, char bit) {
        unsigned int result = 0;
        if (bit == '1') {
            result = static_cast<unsigned int>(std::pow(2, position));
        }
        position++;
        return sum + result;
    });

    return sum;
}

unsigned int
calc(const std::vector<std::string> &input, const std::function<char(unsigned int, unsigned int)> &decision) {

    std::vector<std::string> binaries1;
    std::vector<std::string> binaries2;

    std::copy(input.begin(), input.end(), std::back_inserter(binaries1));
    std::vector<std::string> *source = &binaries1;
    std::vector<std::string> *destination = &binaries2;
    auto count_bits = input[0].size();
    for (std::size_t position = 0; position < count_bits; position++) {
        auto count_0 = std::count_if(source->begin(), source->end(),
                                     [position](const std::string &byte) { return (byte[position] == '0'); });
        auto count_1 = source->size() - count_0;

        auto to_copy = decision(count_1, count_0) ? '1' : '0';
        std::copy_if(source->begin(), source->end(), std::back_inserter(*destination),
                     [position, to_copy](const std::string &byte) {
                         return (byte[position] == to_copy);
                     });
        if (destination->size() > 1) {
            source->clear();
            std::vector<std::string> *temp = source;
            source = destination;
            destination = temp;
        } else {
            break;
        }
    }
    return convert_2_decimal(*destination->begin());
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if (!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> binaries;
    while (std::getline(input_data, line)) {
        binaries.push_back(line);
    }
    input_data.close();

    std::function<char(unsigned int, unsigned int)> greater_then = [](unsigned int a, unsigned int b) {
        return a >= b;
    };
    std::function<char(unsigned int, unsigned int)> lesser_then = [](unsigned int a, unsigned int b) { return a < b; };

    auto oxygen = calc(binaries, greater_then);
    auto co2 = calc(binaries, lesser_then);

    std::cout << "The solution is: " << oxygen * co2 << std::endl;
    return 0;
}
