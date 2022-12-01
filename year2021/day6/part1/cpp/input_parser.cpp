//
// Created by hawk on 18.06.22.
//

#include <regex>
#include <iostream>
#include "input_parser.h"

std::vector<unsigned int> input_parser::parse_line(const std::string &input_line) {
    std::smatch matches;
    std::regex reg( R"((\d+))" );
    std::vector<unsigned int> result;

    std::string str = input_line;
    while(std::regex_search(str, matches, reg)) {
        for(int i=1; i < matches.size(); i++) {
            result.push_back(std::atoi(matches.str(i).c_str()));
        }
        str = matches.suffix().str();
    }
    return result;
}
