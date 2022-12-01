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
    static std::optional<std::vector<unsigned int>> get_vector_from_string(const std::string &line);
};


#endif //ADVENT_OF_CODE_INPUT_PARSER_H
