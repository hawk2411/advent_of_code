//
// Created by hawk on 18.06.22.
//
#include <trim_functions.h>

#include "input_parser.h"

namespace year2022_day1 {

    unsigned int get_number(const std::string &string_number) {
        char *error_break;;
        auto result = std::strtol(string_number.c_str(), &error_break, 10);
        return result;
    }
}
