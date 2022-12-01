//
// Created by hawk on 02.05.22.
//
#include <string>
#include <memory>
#include "BingoBoard.h"

BingoBoard *BingoBoard::createBoard(std::ifstream& input_data) {

    std::string string_line;
    unsigned current_line = 0;

    std::array<std::vector<unsigned int>, 5> bla;

    while(std::getline(input_data, string_line)) {
        if(string_line.empty()) {
            if(current_line == 0)
                continue;
            else
                return nullptr;
        }
        auto numbers = BingoBoard::convert_2_numbers(string_line, ' ');
        if(numbers.empty() || numbers.size() > 5) {
            return nullptr;
        }

        for(int i=0; i < 5; i++) {
            bla[current_line] = numbers;
        }
        current_line++;
        if(current_line >= 5) {
            std::unique_ptr<BingoBoard> board = std::make_unique<BingoBoard>(bla);
            return board.release();
        }
    }

    return nullptr;
}


std::vector<unsigned int> BingoBoard::convert_2_numbers(const std::string& line, char delimiter ) {
    std::vector<unsigned int> result;
    std::string::size_type from = 0;

    auto comma_pos = line.find(delimiter, from);

    while(comma_pos != std::string::npos) {
        std::string string_number = line.substr(from, comma_pos - from);
        if(! string_number.empty())
            result.push_back(std::stoi(string_number));

        from = comma_pos + 1;
        comma_pos = line.find(delimiter, from);
    }
    std::string string_number = line.substr(from, line.size() - from);
    result.push_back(std::stoi(string_number));
    return result;
}

std::pair<bool, unsigned int> BingoBoard::isBingo(unsigned int number) {

    if(!_isActive) {
        return {false, 0};
    }
    auto found = _board.find(number);
    if( found == _board.end())
        return {false,0};

    coord c = found->second;
    _board.erase(found);

    _rows_matched_count[c.x]++;
    _lines_match_count[c.y]++;

    if( (_rows_matched_count[c.x] == 5) || (_lines_match_count[c.y] == 5 )) {
        _isActive = false;
        return {true, getScore(number)};
    }
    return {false,0};
}

unsigned int BingoBoard::getScore(unsigned int number) const {
    unsigned int result = 0;
    for(const auto& [key, value] : _board) {
        result += key;
    }
    result *= number;
    return result;
}

BingoBoard::BingoBoard(const std::array<std::vector<unsigned int>, 5> &bingo_data) {
    for(unsigned int y = 0; y < 5; y++) {
        for(unsigned int x = 0; x < 5; x++) {
            _board[bingo_data[y][x]] = coord{x,y};
        }
    }
}

