#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stack>
#include <vector>
#include <optional>
#include <regex>

constexpr int max_stacks = 9;

struct move_command_t {
    unsigned int crates_to_move;
    std::size_t from;
    std::size_t to;

    static move_command_t init(const std::string& input) {
        move_command_t result {0, 0, 0};
        if(input.empty()) {
            return result;
        }
        std::regex digit_regex("\\d+");

        auto digits_begin =
                std::sregex_iterator(input.begin(), input.end(), digit_regex);

        result.crates_to_move = strtoul( (*digits_begin).str().c_str(), nullptr, 10);
        digits_begin++;
        result.from = strtoul((*digits_begin).str().c_str(), nullptr, 10);
        digits_begin++;
        result.to = strtoul((*digits_begin).str().c_str(), nullptr, 10);

        return result;
    }
};

std::array<std::stack<char>, max_stacks> create_stacks(const std::vector<std::string> &stacks_init_data)
{
    std::array<std::stack<char>, max_stacks> result;

    for(auto it = stacks_init_data.rbegin(); it != stacks_init_data.rend(); it++) {
        for( std::size_t stack_nr = 0; stack_nr < result.size(); stack_nr++) {
            auto position = stack_nr * 4 + 1;
            if( position > (*it).size())
            {
                continue;
            }
            auto crate = (*it)[position];
            if ( crate < 65 || crate > 90 )
            {
                continue;
            }
            result[stack_nr].push(crate);
        }
    }

    return result;
}

std::string interpret_move_commands(std::array<std::stack<char>, 9>& stacks,
                                    const std::vector<std::string>& move_commands)
{

    for(const auto& command: move_commands) {

        auto move_command = move_command_t::init(command);

        std::stack<char> temp_stack;
        for(auto i = 0u; i < move_command.crates_to_move; i++ ) {
            auto crate = stacks[move_command.from-1].top();
            temp_stack.push(crate);
            stacks[move_command.from-1].pop();
        }

        for(auto i=0u; i < move_command.crates_to_move; i++ ) {
            stacks[move_command.to-1].push(temp_stack.top());
            temp_stack.pop();
        }
    }

    std::string result;
    for(const auto& stack :  stacks) {
        if(stack.empty()) continue;

        result += stack.top();
    }
    return result;
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

    std::string result = interpret_move_commands(stacks, move_commands);

    std::cout << "Solution: " << result << std::endl;
    return 0;
}


