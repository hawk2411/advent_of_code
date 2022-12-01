#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include "BingoBoard.h"


int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    std::string line;
    std::getline(input_data, line);

    auto random_numbers = BingoBoard::convert_2_numbers(line, ',');
    std::vector<std::unique_ptr<BingoBoard>> boards;

    BingoBoard* bingoBoard =  BingoBoard::createBoard(input_data);
    while (bingoBoard != nullptr) {
        boards.push_back(std::unique_ptr<BingoBoard>(bingoBoard));
        bingoBoard =  BingoBoard::createBoard(input_data);
    }
    input_data.close();


    unsigned int score = 0;
    for(const auto& number: random_numbers) {
        for(const auto& board : boards) {
            auto result = board->isBingo(number);
            if( result.first ) {
                score = result.second;
            }
        }
    }

    std::cout << "solution found: " << score << std::endl;
    return 1;
}
