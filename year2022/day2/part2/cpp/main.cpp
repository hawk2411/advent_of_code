#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <map>
#include <set>
#include "input_parser.h"



// A -> win against C 1
// B -> win against A 2 pts
// C -> win against B 3

unsigned int getPoints(const char opponent, const char me) {
    auto opponent1 = (opponent - 'A')+1;
    auto me1 = (me - 'A')+1;
    if(me1 == opponent1) {
        //drawn
        return me1 + 3;
    }
    if( ((me1 - opponent1) == 1 ) || ((me1 - opponent1) == -2)){
        return me1 + 6;
    }
    return me1;
}

char calcMyShape(const char shape, const char command) {
    char result = shape;
    if(command == 'Y') { return result; }

    if(command == 'X') {
        switch(shape) {
            case 'A':
                result = 'C';
                break;
            case 'B':
                result ='A';
                break;
            case 'C':
                result = 'B';
                break;
            default:
                result = shape;
        }
    } else {
        switch (shape) {
            case 'A':
                result = 'B';
                break;
            case 'B':
                result = 'C';
                break;
            case 'C':
                result = 'A';
                break;
            default:
                result = shape;
        }
    }
    return result;
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
        const char opponentShape = text_line[0];
        const char command = text_line[2];
        const char myShape = calcMyShape(opponentShape, command);
        auto points = getPoints(opponentShape, myShape);
        sum += points;
    }
    input_data.close();


    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


