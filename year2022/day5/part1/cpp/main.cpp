#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stack>
#include <vector>

std::unique_ptr<std::array<std::stack<char>, 9>> create_stacks(const std::vector<std::string> &stacks_init_data)
{
    auto result = std::make_unique<std::array<std::stack<char>, 9>>();

    return result;
}

std::string interpret_move_commands(const std::array<std::stack<char>, 9>& stacks,
                                    const std::vector<std::string>& move_commands)
{
    return {};
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }

    std::vector<std::string> stacks_input_data;
    std::vector<std::string> move_commands;
    std::string text_line;
    while(std::getline(input_data, text_line)) {
        if(!text_line.empty()) {
            stacks_input_data.push_back(text_line);
            continue;
        }
        break;
    }

    while(std::getline(input_data, text_line)) {
        if(!text_line.empty()) {
            move_commands.push_back(text_line);
            continue;
        }
        break;
    }

    input_data.close();

    auto stacks = create_stacks(stacks_input_data);

    std::string result = interpret_move_commands(*stacks, move_commands);

    std::cout << "Solution: " << result << std::endl;
    return 0;
}


