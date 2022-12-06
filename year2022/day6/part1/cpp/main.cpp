#include <iostream>
#include <fstream>
#include <string>

bool is_signal(const std::string &signal_part)
{
    for(std::size_t i = 0; i < signal_part.size(); i++)
    {
        for(std::size_t n = 0; n < signal_part.size(); n++)
        {
            if( n == i ) { continue; }
            if( signal_part[i] == signal_part[n])
            {
                return false;
            }
        }
    }
    return true;
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
        break;
    }
    input_data.close();

    std::size_t result = 0;

    for(std::size_t i = 0; i < text_line.size() - 4; i++) {
        auto signal_part = text_line.substr(i, 4);

        if( is_signal(signal_part)) {
            result = i + 4;
            break;
        }
    }
    std::cout << "Solution: " << result << std::endl;
    return 0;
}


