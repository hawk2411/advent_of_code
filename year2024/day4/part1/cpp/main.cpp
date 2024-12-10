#include <iostream>
#include <fstream>
#include <string>
#include <trim_functions.h>
#include <regex>

const std::string XMAS = "XMAS";

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

bool SearchForWord(const std::vector<std::string>& map, int x, int y, int x_dir, int y_dir)
{
    for( auto c = 1; c < XMAS.size(); c++)
    {
        if( ! SearchForChar( map, XMAS[c], x + c*x_dir, y + c*y_dir))
        {
            return false;
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
            if( map[y][x] == 'X')
            {
                //found start_point
                if( SearchForWord( map, x,y, 1,0) )   //right
                {
                    sum++;
                }
                if( SearchForWord(map, x,y,-1,0)) //left
                {
                    sum++;
                }
                if( SearchForWord(map, x,y,0,1)) //down
                {
                    sum++;
                }
                if( SearchForWord(map, x,y,0,-1)) //up
                {
                    sum++;
                }
                if( SearchForWord( map, x,y,1,1)) // right down
                {
                    sum++;
                }
                if( SearchForWord( map, x,y,1,-1)) // right up
                {
                    sum++;
                }
                if( SearchForWord(map, x,y,-1,1)) // left down
                {
                    sum++;
                }
                if( SearchForWord( map, x,y,-1,-1)) // left up
                {
                    sum++;
                }

            }
        }
    }
    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


