//
// Created by hawk on 18.06.22.
//
#include <iostream>
#include <algorithm>

#include "input_parser.h"

using namespace day9;

std::vector<int> input_parser::get_numbers(const std::string &line) {
    constexpr unsigned char ascii_zero = 48;
    std::vector<int> result;

    std::transform(line.cbegin(), line.cend(), std::back_inserter(result),
                   [&ascii_zero](const auto& character){
        return character - ascii_zero;
    });

    return result;
}
