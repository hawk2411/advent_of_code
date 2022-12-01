//
// Created by hawk on 18.06.22.
//
#include <iostream>
#include <regex>
#include <sstream>
#include <array>

#include <trim_functions.h>

#include "input_parser.h"



unsigned int input_parser::get_number(const std::string &line) {
    unsigned int result = 0;
    std::string what_ever;
    std::stringstream ss(line);

    std::array<std::string, 2> line_pipe_split;
    int i=0;
    while( std::getline(ss, what_ever, '|') ) {
        string_trimmer::trim(what_ever);
        line_pipe_split[i] = what_ever;
        i++;
    }

    ss.clear();
    ss.str(line_pipe_split[1]);
    while(std::getline(ss, what_ever, ' ') ) {
        string_trimmer::trim(what_ever);
        if(what_ever.empty()) {
            continue;
        }
        auto seq_count= what_ever.size();

        switch(seq_count) {
            case 2:
            case 3:
            case 4:
            case 7:
                result++;
                break;
            default:
                break;
        }

    }
    return result;
}
