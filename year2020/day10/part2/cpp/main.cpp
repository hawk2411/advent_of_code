#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <set>
#include <vector>
#include <cmath>

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::string line;
    std::set<long> ordered_data;

    while(std::getline(input_data, line)) {
        char* converting_error;
        auto number = std::strtol(line.c_str(), &converting_error, 10);
        ordered_data.insert(number);
    }
    input_data.close();

    auto greatest_number =*ordered_data.rbegin();
    auto smallest_number = *ordered_data.begin();

    std::vector<long> must_have;
    unsigned int variations = 0;
    long prev_number = greatest_number + 3;
    while(prev_number > smallest_number) {
        for(auto diff : {3,2,1}) {
            auto must_have_number = prev_number - diff;
            if( ordered_data.contains(must_have_number) ) {
                must_have.push_back(must_have_number);
                prev_number = must_have_number;
                break;
            }
        }

    }

    auto diff = ordered_data.size() - must_have.size();
    std::cout << "Solution is: " <<  diff << std::endl;
    std::cout << pow(2, diff) << "\n";
    return 0;
}
