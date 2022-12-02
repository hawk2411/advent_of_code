#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <set>
#include <array>
#include "input_parser.h"

using coord_t = std::pair<int , int>;
using basin_t = std::vector<coord_t>;


void fillBasin(const coord_t &current_pos, std::set<coord_t> &checked_coords,
               const std::vector<std::vector<int>> &height_map, basin_t &basin)
{
    if(current_pos.first < 0) {
        return;
    }
    if(current_pos.first >= height_map.size()) {
        return;
    }
    if(current_pos.second < 0 ) {
        return;
    }
    if(current_pos.second >= height_map[current_pos.first].size()) {
        return;
    }
    if(checked_coords.contains(current_pos)) {
        return;
    }
    if(height_map[current_pos.first][current_pos.second] == 9 )
    {
        return;
    }

    basin.push_back(current_pos);
    checked_coords.insert(current_pos);

    coord_t next_direction;
    coord_t next_pos;

    next_direction.first = 0;
    next_direction.second = -1;
    next_pos.first = current_pos.first + next_direction.first;
    next_pos.second = current_pos.second + next_direction.second;
    fillBasin(next_pos, checked_coords, height_map, basin);

    next_direction.first = 0;
    next_direction.second = 1;
    next_pos.first = current_pos.first + next_direction.first;
    next_pos.second = current_pos.second + next_direction.second;
    fillBasin(next_pos, checked_coords, height_map, basin);

    next_direction.first = -1;
    next_direction.second = 0;
    next_pos.first = current_pos.first + next_direction.first;
    next_pos.second = current_pos.second + next_direction.second;
    fillBasin(next_pos, checked_coords, height_map, basin);

    next_direction.first = 1;
    next_direction.second = 0;
    next_pos.first = current_pos.first + next_direction.first;
    next_pos.second = current_pos.second + next_direction.second;
    fillBasin(next_pos, checked_coords, height_map, basin);
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

    std::multiset<std::size_t> basins;
    std::set<coord_t> progress;


    for(int row = 0; row < height_map.size(); ++row) {
        for(int col = 0; col < height_map[row].size(); ++col) {
            if( height_map[row][col] == 9 ) {
                continue;
            }
            coord_t current_pos(row, col);
            if(progress.contains(current_pos)) {
                continue;
            }
            basin_t basin;
            fillBasin(current_pos, progress, height_map, basin);
            if(basin.empty()) {
                continue;
            }
            basins.insert(basin.size());
        }
    }

    auto product = 1ul;
    auto last = basins.rbegin();
    for(int i = 0; i < 3; i++ ) {
        product *= *last;
        last++;
    }
    std::cout << "Solution: " << product << std::endl;

    return 0;
}


