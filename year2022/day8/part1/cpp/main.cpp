#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

bool isVisible(std::size_t  x, std::size_t y, const std::vector<std::vector<int>>& forest) {

    auto current_tree = forest[y][x];

    bool visible = true;
    //looking from left
    for( std::size_t i = 0; i < x; i++ ) {
        if( forest[y][i] >= current_tree ) {
            visible = false;
            break;
        }
    }

    if(visible) { return visible; }

    visible = true;
    //looking from right
    for( std::size_t i = x+1; i < forest[0].size(); i++ ) {
        if(forest[y][i] >= current_tree) {
            visible = false;
            break;
        }
    }

    if(visible) { return visible; }

    visible = true;
    //looking from top
    for( std::size_t i = 0; i < y; i++ ) {
        if(forest[i][x] >= current_tree) {
            visible = false;
            break;
        }
    }

    if(visible) { return visible; }

    visible = true;
    //looking from bottom
    for( std::size_t i = y+1; i < forest.size(); i++ ) {
        if(forest[i][x] >= current_tree) {
            visible = false;
            break;
        }
    }

    return visible;
}

auto getVisibleTrees(const std::vector<std::vector<int>>& forest) {

    auto countVisibleTrees = 0;
    auto right_border = forest[0].size();
    auto bottom_border = forest.size();

    for(std::size_t row = 0; row < bottom_border; row++) {

        for(std::size_t column = 0; column < right_border; column++) {
            if( row == 0 ||  column == 0 ) {
                countVisibleTrees++;
                continue;
            }
            if (row == (bottom_border - 1) || column == (right_border - 1)) {
                countVisibleTrees++;
                continue;
            }
            if(isVisible(column, row, forest) )  {
                countVisibleTrees++;
                continue;
            }
        }
    }
    return countVisibleTrees;
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    std::string text_line;
    std::vector<std::vector<int>> forest;
    constexpr int ASCII_NULL = 48;
    while(std::getline(input_data, text_line)) {
        std::vector<int> forest_column;

        for(const auto& c : text_line) {
            forest_column.push_back(c - ASCII_NULL);
        }
        forest.push_back(forest_column);
    }
    input_data.close();

    auto result = getVisibleTrees(forest);

    std::cout << "Solution: " << result << std::endl;
    return 0;
}


