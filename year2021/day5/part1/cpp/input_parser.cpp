//
// Created by hawk on 18.06.22.
//
#include <iostream>
#include <regex>
#include "input_parser.h"

using namespace day5_part1;
std::optional<std::pair<point, point>> input_parser::get_vector_from_string(const std::string &line) {

    std::smatch matches;
    std::regex reg( R"((\d+),(\d+)\s*->\s*(\d+),(\d+))" );

    if(!std::regex_match(line, matches, reg))
        return std::nullopt;

    unsigned int x1 = std::atoi(matches.str(1).c_str());
    unsigned int y1 = std::atoi(matches.str(2).c_str());

    unsigned int x2 = std::atoi(matches.str(3).c_str());
    unsigned int y2 = std::atoi(matches.str(4).c_str());

    if(x1 == x2 || y1 == y2)
        return std::make_pair(point(x1,y1), point(x2,y2));
    else
        return std::nullopt;
}

std::vector<point> input_parser::get_points_from_vector(const std::pair<point, point>& vector_2d) {
    std::vector<point> result;

    auto x1 = vector_2d.first.getX();
    auto x2 = vector_2d.second.getX();

    auto y1 = vector_2d.first.getY();
    auto y2 = vector_2d.second.getY();

    point new_point {x1, y1};
    result.push_back(new_point);

    do {
        if((x1 != x2))
            x1 += (x1 < x2) ? 1 : -1;

        if(y1 != y2)
            y1 += (y1 < y2) ? 1 : -1;

        new_point.setX(x1);
        new_point.setY(y1);
        result.push_back(new_point);
    } while (new_point != vector_2d.second);

    return result;
}

