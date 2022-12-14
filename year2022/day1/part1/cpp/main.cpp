#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <map>
#include <set>
#include "input_parser.h"



int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    auto sum  = 0u;
    std::multiset<decltype(sum)> sums;

    std::string text_line;
    while(std::getline(input_data, text_line)) {
        if( text_line.empty() ) {
            sums.insert(sum);
            sum = 0u;
            continue;
        }
        sum += year2022_day1::get_number(text_line);
    }
    input_data.close();

    if(sum > 0) {
        sums.insert(sum);
    }
    auto last = sums.rbegin();
    sum = 0;
    for(int i = 0; i < 3; i++ ) {
        sum += *last;
        last++;
    }

    std::cout << "Solution: " << *sums.rbegin() << std::endl;
    return 0;
}


