//
// Created by hawk on 18.06.22.
//
#include <regex>
#include <trim_functions.h>
#include "unique_sequences.h"
#include "input_parser.h"


// trim from start (in place)
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

    unique_sequences us(line_pipe_split[0]);

    ss.clear();
    ss.str(line_pipe_split[1]);

    unsigned int tausend = 1000;

    std::string number;

    while (std::getline(ss, number, ' ')) {
        string_trimmer::trim(number);
        if (number.empty()) {
            continue;
        }
        auto n = us.getNumber(number);
        result += n * tausend;
        tausend = tausend / 10;
    }

    return result;
}
