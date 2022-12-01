#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    std::string line;
    int horizontal = 0;
    int depth = 0;

    while (std::getline(input_data, line)) {
        auto pos = line.find_first_of(' ');
        int coord = std::stoi(line.substr(pos+1));
        std::string command = line.substr(0, pos);
        if(command == "forward" ) {
            horizontal += coord;
            continue;
        }
        if(command == "up" ) {
            depth -= coord;
            continue;
        }
        depth += coord;
    }
    input_data.close();

    std::cout << "The solution is: " << horizontal*depth << std::endl;
    return 0;
}
