//
// Created by hawk on 18.06.22.
//

#ifndef ADVENT_OF_CODE_INPUT_PARSER_H
#define ADVENT_OF_CODE_INPUT_PARSER_H


#include <utility>
#include <string>
#include <vector>
#include <optional>

class input_parser {

public:
    static unsigned int get_number(const std::string &line);
};


#endif //ADVENT_OF_CODE_INPUT_PARSER_H
