#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if (!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    std::string line;
    std::vector<int> numbers;
    while (std::getline(input_data, line)) {
        numbers.push_back(std::stoi(line));
    }
    input_data.close();

    unsigned int increase = 0;
    for (auto number = numbers.begin(); number != numbers.end() - 3; number++) {
        int sum = std::accumulate(number, number + 3, 0);
        int next_sum = std::accumulate(std::next(number), std::next(number) + 3, 0);
        increase += (next_sum > sum) ? 1 : 0;
    }
    std::cout << "The solution is: " << increase << std::endl;
    return 0;
}
