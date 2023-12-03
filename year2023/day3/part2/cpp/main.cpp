#include <iostream>
#include <fstream>
#include <string>
#include <trim_functions.h>
#include <map>
#include <set>
#include <vector>
#include <cassert>

struct point_t {
    int x {0};
    int y {0};

    bool operator<(const point_t& right) const {
        if(y < right.y) {
            return true;
        }
        if( y > right.y ) {
            return false;
        }
        if(x < right.x) {
            return true;
        }
        return false;
    }

};
bool is_empty(const char c) { return (c == '.');}

bool is_symbol(const char c) {
    if(is_empty(c)) { return false; }
    if(std::isdigit(static_cast<unsigned char>(c))) { return false; }
    return true;
}

std::map<point_t, char> symbols;
std::vector<std::string> strings;

long GetNumber(int x, int y) {

    if(x < 0 || y < 0) {
        return 0;
    }
    if(y >= strings.size()) {
        return 0;
    }
    if(x >= strings.at(y).size()) {
        return 0;
    }

    if(!std::isdigit(strings.at(y).at(x))) {
        return 0;
    }

    int start_pos;
    for(start_pos = x; start_pos >= 0; start_pos--) {
        if( !std::isdigit( strings.at(y).at(start_pos))) {
            break;
        }
    }
    start_pos++;
    int end_pos;
    for(end_pos = start_pos; end_pos < strings[y].size(); end_pos++) {
        if(!std::isdigit(strings.at(y).at(end_pos))) {
            break;
        }
    }
    std::string sub = strings.at(y).substr(start_pos, end_pos-start_pos);
    char * pEnd;
    return strtol(sub.c_str(), &pEnd, 10);
}

long GetNumberDiagonal(int x, int y) {
    long sum = GetNumber(x-1, y);
    sum += GetNumber(x+1, y);

    return sum;
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    std::string text_line;
    while(std::getline(input_data, text_line)) {
        strings.push_back(text_line);
        for(int i = 0; i < text_line.size();  ++i) {
            point_t point (i, strings.size()-1);
            if(is_symbol(text_line.at(i))) {
               symbols.insert(std::pair<point_t, char>(point, text_line[i]));
            }
        }
    }
    long sum = 0;

    for(const auto& [p, symbol] : symbols) {
        if (!is_symbol(symbol)) {
            continue;
        }

        long symbol_sum = 0;
        //check for numbers above
        long number = GetNumber(p.x, p.y - 1);
        symbol_sum += number;
        if (number == 0) {
            symbol_sum += GetNumberDiagonal(p.x, p.y - 1);
        }

        symbol_sum += GetNumber(p.x - 1, p.y);
        symbol_sum += GetNumber(p.x + 1, p.y);

        number = GetNumber(p.x, p.y + 1);
        symbol_sum += number;
        if (number == 0) {
            symbol_sum += GetNumberDiagonal(p.x, p.y + 1);
        }

        sum += symbol_sum;
        std::cout << "Symbol: '" << symbol << "' (" << p.x << " | " << p.y << ") = " << symbol_sum << "\n";
    }


    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


