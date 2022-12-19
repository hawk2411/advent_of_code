#include <iostream>
#include <fstream>
#include <string>

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    std::string text_line;
    while(std::getline(input_data, text_line)) {
        break;
    }
    input_data.close();

    std::size_t result = 0;

    std::cout << "Solution: " << result << std::endl;
    return 0;
}


