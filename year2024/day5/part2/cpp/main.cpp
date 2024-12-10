#include <iostream>
#include <fstream>
#include <string>
#include <trim_functions.h>
#include <regex>
#include <set>
#include <sstream>


using pages_t = std::vector<std::string>;
using print_commands_t = std::vector<pages_t>;
using rules_t = std::set<std::string>;

void Swap(pages_t &pages, std::size_t current)
{
    auto next = current + 1;
    const auto temp = pages.at(current);
    pages[current] = pages.at(next);
    pages[next] = temp;
}

bool CheckCurrentPair(const rules_t &rules, const pages_t &pages, std::size_t pos)
{
    const auto next = pos + 1;
    if( next < pages.size())
    {
        std::string rule = pages.at(pos) + "|" + pages.at(next);

        return rules.contains(rule);
    }
    return false;
}

std::pair<bool, std::size_t> ArePagesCorrect( const rules_t& rules, const pages_t &pages)
{
    std::pair<bool, std::size_t> result{true, 0};

    for(auto i = 0; i < pages.size()-1; ++i)
    {
        //create rule
        if(!CheckCurrentPair(rules, pages, i))
        {
            result.first = false;
            result.second = i;
            return result;
        }
    }
    return result;
}

bool DoCorrection(const rules_t& rules, pages_t &pages, std::size_t current_position = 0)
{

    if( current_position > pages.size() -1 )
    {
        return false;
    }
    Swap( pages, current_position);
    auto swapResult = ArePagesCorrect(rules, pages);
    if(swapResult.first)
    {
        return true;
    }
    if( swapResult.second == current_position)
    {
        Swap(pages, current_position); //back
        return DoCorrection(rules, pages, current_position + 1);
    }
    else
        return DoCorrection(rules, pages, swapResult.second);
}

int GetMiddlePage(const pages_t& pages)
{
    const auto middlePageIndex = (pages.size() / 2 ) ;
    const auto middlePage = std::stoi(pages.at(middlePageIndex));
    return middlePage;
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
    std::set<std::string> rules;
    print_commands_t print_commands;

    bool readRules = true;
    while(std::getline(input_data, text_line)) {
        string_trimmer::trim(text_line);
        if(text_line.empty()) {
            if( readRules )
            {
                readRules = false;
                continue;   //at the first occurrence jump over the empty line
            }
            else
            {
                break;
            }
        }
        if(readRules)
        {
            rules.insert(text_line);
        }
        else
        {
            pages_t pages;
            std::stringstream ss(text_line);
            std::string strDigit;
            const char delimiter = ',';
            while( getline(ss, strDigit, delimiter))
            {
                pages.push_back(strDigit);
            }
            print_commands.push_back(pages);
        }
    }

    for( auto& pages : print_commands)
    {
        auto result = ArePagesCorrect(rules, pages);
        if(!result.first)
        {
            DoCorrection(rules, pages, result.second);
            sum += GetMiddlePage(pages);
        }
    }
    std::cout << "Solution: " << sum << std::endl;
    return 0;
}



