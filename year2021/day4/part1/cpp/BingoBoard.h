//
// Created by hawk on 02.05.22.
//

#ifndef ADVENT_OF_CODE_BINGO_BOARD_DAY4_P1_H
#define ADVENT_OF_CODE_BINGO_BOARD_DAY4_P1_H
#pragma once

#include <array>
#include <vector>
#include <fstream>
#include <map>

struct coord {
    unsigned int x;
    unsigned int y;
};

class BingoBoard {
private:
    std::map<unsigned int, coord> _board;
    std::array<unsigned int, 5> _rows_matched_count{0, 0, 0, 0, 0};
    std::array<unsigned int, 5> _lines_match_count{0, 0, 0, 0, 0};

    [[nodiscard]] unsigned int getScore(unsigned int number) const;

public:
    explicit BingoBoard(const std::array<std::vector<unsigned int>, 5> &bingo_data);

    std::pair<bool, unsigned int> isBingo(unsigned int number);

    static BingoBoard *createBoard(std::ifstream &input_data);

    static std::vector<unsigned int> convert_2_numbers(const std::string &line, char delimiter);
};


#endif //ADVENT_OF_CODE_BINGO_BOARD_DAY4_P1_H
