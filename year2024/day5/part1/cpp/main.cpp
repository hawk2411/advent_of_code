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

bool ArePagesCorrect( const rules_t& rules, const pages_t &pages)
{
    for(auto i = 0; i < pages.size()-1; ++i)
    {
        //create rule
        std::string rule = pages.at(i) + "|" + pages.at(i + 1);
        if(!rules.contains(rule))
        {
            return false;
        }
    }
    return true;
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

    for( const auto& pages : print_commands)
    {
        if( ArePagesCorrect(rules, pages))
        {
            sum += GetMiddlePage(pages);
        }
    }
    std::cout << "Solution: " << sum << std::endl;
    return 0;
}



