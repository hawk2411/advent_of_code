#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <map>
#include <optional>
#include "input_parser.h"


struct position_cost_item
{
    unsigned int position;
    unsigned int costs;
};

position_cost_item calc_cheapest_position(const std::vector<unsigned int> &positions);

position_cost_item check_position(unsigned int pos, const std::map<unsigned int, unsigned int> &crabs_positions);

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    std::string text_line;

    unsigned int sum = 0;
    std::vector<unsigned int> positions;

    while(std::getline(input_data, text_line)) {
        positions = input_parser::get_vector_from_string(text_line);

        position_cost_item result = calc_cheapest_position(positions);
        sum = result.costs;
        break;
    }

    input_data.close();


    std::cout << "Solution: " << sum << std::endl;
    return 1;
}

position_cost_item calc_cheapest_position(const std::vector<unsigned int> &positions) {
    std::map<unsigned int, unsigned int> count_crabs_on_same_position;

    if(positions.empty())
        return {0,0};

    for(const auto& pos : positions) {
        auto position = count_crabs_on_same_position.find(pos);
        if(position == count_crabs_on_same_position.end()) {
            count_crabs_on_same_position[pos] = 1;
        } else {
            position->second++;
        }
    }

    position_cost_item result {};
    bool first_time = true;
    auto last_position = count_crabs_on_same_position.rbegin()->first; //greatest position
    for(unsigned int i = 0 ; i <= last_position; i++) {

        position_cost_item cost = check_position(i,  count_crabs_on_same_position);
        if(first_time) {
            result = cost;
            first_time = false;
        } else {
            if(result.costs > cost.costs) {
                result = cost;
            }
        }
    }

    return result;
}

position_cost_item check_position(const unsigned int position,
                                  const std::map<unsigned int, unsigned int> &crabs_positions) {

    position_cost_item result = {position, 0};
    for(const auto [pos, count] : crabs_positions) {
        if( pos == position) {
            continue;
        }

        auto m = std::max(position, pos);
        auto n = std::min(position, pos);
        auto diff = m - n;
        unsigned int cost = (diff * (diff+1)) / 2;

        result.costs += cost * count;
    }

    return result;
}

