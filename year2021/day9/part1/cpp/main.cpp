#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <map>
#include "input_parser.h"


std::vector<int> getLowestPositions(const std::vector<std::vector<int>> &height_map) {

    std::vector<int> result;

    const auto row_max = height_map.size();
    for( std::size_t row = 0; row < row_max; ++row) {
        const auto column_max = height_map[row].size();

        for(std::size_t column = 0; column < column_max; ++column ) {
            auto height = height_map[row][column];

            if(column < column_max -1) {
                if( height_map[row][column+1] <= height) {
                    continue;
                }
            }
            if(column > 0) {
                if( height_map[row][column-1] <= height) {
                    continue;
                }
            }

            if(row < row_max -1) {
                if( height_map[row+1][column] <= height) {
                    continue;
                }
            }
            if(row > 0) {
                if( height_map[row-1][column] <= height) {
                    continue;
                }
            }

            result.push_back(height);
        }
    }
    return result;
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    std::string text_line;


    std::vector<std::vector<int>> height_map;
    while(std::getline(input_data, text_line)) {

        auto height_row = day9::input_parser::get_numbers(text_line);
        height_map.push_back(height_row);
    }
    input_data.close();

    unsigned int sum = 0;
    std::vector<int> lowest_positions = getLowestPositions(height_map);
    for( const auto& height : lowest_positions) {
        sum += height+1;
    }

    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


