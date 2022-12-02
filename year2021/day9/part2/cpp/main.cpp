#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <map>
#include "input_parser.h"



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

    using coord_t = std::pair<int, int>;
    using basin_t = std::vector<coord_t>;
    std::vector<basin_t> basins;
    std::map<coord_t, bool> progress;

    for(auto & row : height_map) {
        for(int col = 0; col < row.size(); ++col) {
            if( row[col] == 9 ) {
                continue;
            }
        }
    }

    std::cout << "Solution: " << 0 << std::endl;
    return 0;
}


