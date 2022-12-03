#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

int getPriority(const char &item) {

    // 27 -  52
    // A = 65 - 38  == 27
    // 1 - 26
    // a = 97 - 96 == 1

    return std::isupper(item) ? item - 38 : item - 96;
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if (!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    unsigned int sum = 0u;
    constexpr auto max_members_in_a_group = 3u;
    std::array<std::string, max_members_in_a_group> group_member;
    std::string text_line;
    int i = 0;
    while (std::getline(input_data, text_line)) {
        group_member[i] = text_line;
        i++;
        if( i == max_members_in_a_group) {
            for(const auto& item : group_member[0]) {
                auto pos = group_member[1].find(item);
                if(pos == std::string::npos) {
                    continue;
                }
                pos = group_member[2].find(item);
                if(pos == std::string::npos) {
                    continue;
                }
                auto priority = getPriority(item);
                sum += priority;
                break;
            }
            i = 0;
        }
    }
    input_data.close();


    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


