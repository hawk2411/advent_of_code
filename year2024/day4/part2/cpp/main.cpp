#include <iostream>
#include <fstream>
#include <string>
#include <trim_functions.h>
#include <regex>

const std::string XMAS = "MAS";

bool SearchForChar(const std::vector<std::string>& map, std::string::value_type value, int x_pos, int y_pos)
{
    if( y_pos < 0 || x_pos < 0 )
    {
        return false;
    }
    if( y_pos >= map.size() )
    {
        return false;
    }
    if( x_pos >= map[y_pos].size())
    {
        return false;
    }
    if( map[y_pos][x_pos] == value )
    {
        return true;
    }
    return false;
}

char GetOppositeChar(char c)
{
    return ( c == 'M' ) ? 'S' : 'M';
}

int  GetOppositeDirection(int x_dir)
{
    return ( x_dir == 1 ) ? -1 : 1;
}

bool SearchForWord(const std::vector<std::string>& map, int x, int y, int x_dir, int y_dir)
{
    if( SearchForChar( map, 'M', x + x_dir, y + y_dir)  )
    {
        if( SearchForChar(map, GetOppositeChar('M'), x + GetOppositeDirection(x_dir), y + GetOppositeDirection(y_dir)) )
        {
            return true;
        }
    }
    else if (SearchForChar( map, 'S', x + x_dir, y + y_dir)  )
    {
        if( SearchForChar(map, GetOppositeChar('S'), x + GetOppositeDirection(x_dir), y + GetOppositeDirection(y_dir)))
        {
            return true;
        }
    }

    return false;
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
    std::vector<std::string> map;

    while(std::getline(input_data, text_line)) {
        string_trimmer::trim(text_line);
        if(text_line.empty()) {
            break;
        }
        map.push_back(text_line);
    }

    for(auto y = 0; y < map.size(); y++)
    {
        for(auto x = 0; x < map[y].size(); x++)
        {
            if( map[y][x] == 'A')
            {
                //found start_point
                if( SearchForWord( map, x,y, 1, 1)  && SearchForWord( map, x,y, 1, -1))   //right down and opposite
                {
                    sum++;
                }
            }
        }
    }
    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


