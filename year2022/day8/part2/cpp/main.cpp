#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <numeric>

std::size_t countVisibleTrees(long  column, long row, const std::vector<std::vector<int>>& forest) {

    if(column == 0 || row == 0 || column == forest[row].size()-1 || row == forest.size()-1) {
        return 0;
    }

    auto view_point = forest[row][column];
    std::array<std::size_t, 4> view_in_each_direction {0,0,0,0};
    auto count_visible_trees = 0ul;

    //looking to left
    for (long x = column - 1; x >= 0; x--) {
        auto tree = forest[row][x];
        view_in_each_direction[0]++;

        if (tree >= view_point) {
            break;
        }
    }

    //looking to right
    for (long x = column + 1; x < forest[row].size(); x++) {
        auto tree = forest[row][x];
        view_in_each_direction[1]++;

        if (forest[row][x] >= view_point) {
            break;
        }
    }

    //looking to top
    for (long y = row - 1; y >= 0; y--) {
        auto tree = forest[y][column];
        view_in_each_direction[2]++;
        if (tree >= view_point) {
            break;
        }
    }

    //looking to bottom
    for (long y = row + 1; y < forest.size(); y++) {
        auto tree = forest[y][column];
        view_in_each_direction[3]++;
        if (tree >= view_point) {
            break;
        }
    }

    return std::accumulate(view_in_each_direction.cbegin(),view_in_each_direction.cend(), 1,
                                          [](auto res, const auto& value){
        return res*value;
    });
}

std::size_t getPanoramaProduct(const std::vector<std::vector<int>>& forest) {

    auto maxVisibleTrees = 0ul;
    auto right_border = forest[0].size();
    auto bottom_border = forest.size();

    for(std::size_t row = 0; row < bottom_border; row++) {

        for(std::size_t column = 0; column < right_border; column++) {

            auto trees = countVisibleTrees(static_cast<long>(column), static_cast<long>(row), forest);
            if(trees > maxVisibleTrees) {
                maxVisibleTrees = trees;
            }
        }
    }
    return maxVisibleTrees;
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

    auto result = getPanoramaProduct(forest);

    std::cout << "Solution: " << result << std::endl;
    return 0;
}


