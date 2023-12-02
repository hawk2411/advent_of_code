#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <trim_functions.h>
#include <sstream>
#include <optional>
#include <cassert>


struct game_move_t {
    long red {0};
    long green {0};
    long blue {0};
};

struct game_t {
    long id {0};

    std::vector<game_move_t> moves;
};

long GetGameId(std::string& game_string) {
    std::stringstream ss(game_string);
    if(ss.good()) {
        std::string substring;
        std::getline(ss, substring, ' ');
    }

    if(ss.good()) {
        std::string id_string;
        std::getline(ss, id_string, ' ');

        char *error_break;;
        return std::strtol(id_string.c_str(), &error_break, 10);

    }
    return -1;
}

game_move_t CreateGameMove(const std::string &move) {

    std::stringstream ss(move);
    game_move_t gameMove;
    while(ss.good()) {
        std::string cubes;
        std::getline(ss, cubes, ',');

        string_trimmer::trim(cubes);
        std::stringstream colorStream (cubes);

        long countColor = 0;
        if(colorStream.good()) {
            std::string digit;
            std::getline(colorStream, digit, ' ');
            char *error_break;;
            countColor = std::strtol(digit.c_str(), &error_break, 10);
        }
        if(colorStream.good()) {
            std::string color;
            std::getline(colorStream, color, ' ');

            if(color == "green") {
                gameMove.green += countColor;
            }
            if(color == "red") {
                gameMove.red += countColor;
            }
            if(color == "blue") {
                gameMove.blue += countColor;
            }
        }
    }
    return gameMove;
}

std::vector<game_move_t> GetGameMoves(const std::string &moves) {
    std::stringstream ss(moves);

    std::vector<game_move_t> game_moves;
    while(ss.good()) {
        std::string move;
        std::getline(ss, move, ';');
        game_move_t gameMove =  CreateGameMove(move);
        game_moves.push_back(gameMove);
    }
    return game_moves;
}

std::optional<game_t> ReadGame(const std::string& test_line ) {
    game_t g;

    std::stringstream ss(test_line);

    std::string game_string;
    if(ss.good()) {
        std::getline(ss, game_string, ':');
    }
    else {
        return {};
    }

    std::string moves_string;
    if(ss.good()) {
        std::getline(ss, moves_string, ':');
    } else
    {
        return {};
    }

    g.id = GetGameId(game_string);
    if(g.id < 0) {
        return {};
    }

    g.moves = GetGameMoves(moves_string);

    return g;

}

long GetSumPossibleGames(const std::vector<game_t> &games, int red, int green, int blue) {
    long sum = 0;

    for(const auto& game : games) {
        bool possible = true;
        for(const auto& move : game.moves) {
            if(move.blue > blue) {
                possible = false;
                break;
            }
            if(move.green > green) {
                possible = false;
                break;
            }
            if(move.red > red) {
                possible = false;
                break;
            }
        }
        if(possible) {
            sum += game.id;
        }
    }

    return sum;
}

int main() {

    int MAX_RED = 12;
    int MAX_GREEN = 13;
    int MAX_BLUE = 14;

    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if(!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }


    std::string text_line;
    std::vector<game_t> games;

    while(std::getline(input_data, text_line)) {
        string_trimmer::trim(text_line);
        if(text_line.empty()) {
            break;
        }

        auto g = ReadGame(text_line);
        assert(g.has_value());
        games.push_back(g.value());
    }

    long sum = GetSumPossibleGames(games, MAX_RED, MAX_GREEN, MAX_BLUE);

    std::cout << "Solution: " << sum << std::endl;
    return 0;
}


