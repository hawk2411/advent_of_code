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
    [[nodiscard]] bool areOverlappping(const range& other) const {
        if(other.lower <= this->upper && other.lower >= this->lower) { return true; }
        if(other.upper >= this->lower && other.upper <= this->upper) { return true; }

        if(this->lower <= other.upper && this->lower >= other.lower) { return true; }
        if(this->upper >= other.lower && this->upper <= other.lower) { return true; }

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

    unsigned int sum = 0u;
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

        if(range_left->areOverlappping(*range_right)) {
            sum++;
        }
//        if(range_left->distance() >= range_right->distance()) {
//            if(range_left->includes_complete(*range_right) ) {
//                sum++;
//            }
//        } else {
//            if (range_right->includes_complete(*range_left)) {
//                sum++;
//            }
//        }
    }
    input_data.close();


    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


