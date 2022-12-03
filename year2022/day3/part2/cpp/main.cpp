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

constexpr auto max_members_in_a_group = 3u;

unsigned int getBadgeOfGroup(std::array<std::string, max_members_in_a_group> &group_members) {
    auto result = 0u;
    for (const auto &item: group_members[0]) {

        auto pos = std::string::npos;

        for (int n = 1; n < max_members_in_a_group; n++) {
            pos = group_members[n].find(item);
            if (pos == std::string::npos) {
                break;
            }
        }
        if (pos == std::string::npos) {
            continue;
        }

        result = getPriority(item);
        break;
    }

    return result;
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if (!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    unsigned int sum = 0u;
    std::array<std::string, max_members_in_a_group> group_members;
    std::string text_line;
    int i = 0;
    while (std::getline(input_data, text_line)) {
        group_members[i] = text_line;
        i++;
        if( i < max_members_in_a_group) {
            continue;
        }

        i = 0;
        sum += getBadgeOfGroup(group_members);
    }
    input_data.close();


    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


