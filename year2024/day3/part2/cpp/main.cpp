#include <iostream>
#include <fstream>
#include <string>
#include <trim_functions.h>
#include <regex>

long DoMul(const std::string& command)
{
    std::regex digit_match("\\d{1,3}");
    auto first_match =
        std::sregex_iterator(command.begin(), command.end(), digit_match);
    auto last_match = std::sregex_iterator();
    const auto digit1 = std::stoi(first_match->str());
    ++first_match;
    const auto digit2 = std::stoi(first_match->str());

    return digit1 * digit2;
}

std::string RemoveDoNot(const std::string& programm)
{
    std::string result = programm;
    while (!result.empty())
    {
        auto start_pos = result.find("don't()");

        if (start_pos == std::string::npos)
        {
            return result;
        }

        auto end_pos = result.find("do()", start_pos + 1);
        if (end_pos == std::string::npos)
        {
            result.erase(start_pos, result.size());
        }
        else
        {
            end_pos += 4; // sizeof(do())
            result.erase(start_pos, end_pos - start_pos);
        }
    }
}

int main() {

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    long sum  = 0;

    std::string text_line;
    std::string program;
    while(std::getline(input_data, text_line)) {
        string_trimmer::trim(text_line);
        if(text_line.empty()) {
            break;
        }
        program += text_line;
    }

    program = RemoveDoNot(program);

    std::regex word_regex("mul\\(\\d{1,3},\\d{1,3}\\)");
    auto words_begin =
        std::sregex_iterator(program.begin(), program.end(), word_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found "
                << std::distance(words_begin, words_end)
                << " multiplications\n";

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        sum += DoMul(match.str());
    }
    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


