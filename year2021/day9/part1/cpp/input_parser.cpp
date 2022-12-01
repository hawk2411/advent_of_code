//
// Created by hawk on 18.06.22.
//
#include <iostream>
#include <regex>
#include <trim_functions.h>

#include "input_parser.h"

using namespace day9;

std::vector<int> input_parser::get_numbers(const std::string &line) {
    std::vector<int> result;
    constexpr unsigned char ascii_zero = 48;

    result.reserve(line.size());
    for(const auto& c : line) {
        result.push_back(c - ascii_zero);
    }

    return result;
}
