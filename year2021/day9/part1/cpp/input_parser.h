//
// Created by hawk on 18.06.22.
//

#ifndef ADVENT_OF_CODE_INPUT_PARSER_H
#define ADVENT_OF_CODE_INPUT_PARSER_H


#include <utility>
#include <string>
#include <vector>
#include <optional>

namespace day9 {
    class input_parser {

    public:
        static std::vector<int> get_numbers(const std::string &character);
    };
}

#endif //ADVENT_OF_CODE_INPUT_PARSER_H
