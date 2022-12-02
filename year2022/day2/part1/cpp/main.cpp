#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <map>
#include <set>
#include "input_parser.h"



// A == X -> win against C == Z  1
// B == Y -> win against A == X  2 pts
// C == Z -> win against B == Y  3

unsigned int getPoints(const char opponent, const char me) {
    auto opponent1 = (opponent - 'A')+1;
    auto me1 = (me - 'X')+1;
    if(me1 == opponent1) {
        //drawn
        return me1 + 3;
    }
    if( ((me1 - opponent1) == 1 ) || ((me1 - opponent1) == -2)){
        return me1 + 6;
    }
    return me1;
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
        if(text_line.empty()) {
            continue;
        }
        const char opponent = text_line[0];
        const char me = text_line[2];
        auto points = getPoints(opponent, me);
        sum += points;
    }
    input_data.close();


    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


