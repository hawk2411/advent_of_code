#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

struct range {
    unsigned long lower;
    unsigned long upper;

    [[nodiscard]] unsigned long distance()const {return (upper - lower) +1;}
    [[nodiscard]] bool includes_complete(const range& smaller) const {
        if(smaller.lower < this->lower) { return false; }
        if(smaller.upper > this->upper) { return false; }
        return true;
    }
    static bool areOverlappping(const range& left, const range& right)  {
        if(right.lower <= left.upper && right.lower >= left.lower) { return true; }
        if(right.upper >= left.lower && right.upper <= left.upper) { return true; }

        if(left.lower <= right.upper && left.lower >= right.lower) { return true; }
        if(left.upper >= right.lower && left.upper <= right.lower) { return true; }

        return false;
    }

    static std::unique_ptr<range> fabric(const std::string& init) {
        auto pos = init.find('-');
        if( pos == std::string::npos ) {return nullptr;}

        auto result = std::make_unique<range>();
        result->lower = std::strtoul(init.substr(0, pos).c_str(), nullptr, 10 );
        result->upper = std::strtoul(init.substr(pos+1).c_str(), nullptr, 10);
        return result;
    }
};

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    auto sum = 0u;
    std::string text_line;
    while(std::getline(input_data, text_line)) {
        auto pos = text_line.find(',');
        if(pos == std::string::npos) {
            continue;
        }
        auto left = text_line.substr(0, pos);
        auto right = text_line.substr(pos+1);

        auto range_left = range::fabric(left);
        auto range_right = range::fabric(right);

        sum += (range::areOverlappping(*range_left, *range_right)) ? 1 : 0;
    }
    input_data.close();


    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


