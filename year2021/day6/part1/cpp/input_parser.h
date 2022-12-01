//
// Created by hawk on 18.06.22.
//

#ifndef ADVENT_OF_CODE_INPUT_PARSER_H
#define ADVENT_OF_CODE_INPUT_PARSER_H


#include <vector>
#include <string>

class input_parser {

public:
    static std::vector<unsigned int> parse_line(const std::string &input_line);
};


#endif //ADVENT_OF_CODE_INPUT_PARSER_H
