#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <trim_functions.h>
#include <utility>
#include <vector>

using position_t = std::pair<int, int>;
using direction_t = std::pair<int, int>;

bool do_next_step(const std::vector<std::string>& room, const std::set<position_t>& obstructions, position_t& guard_position, direction_t& guard_direction) {
  int next_x = guard_position.first + guard_direction.first;
  int next_y = guard_position.second + guard_direction.second;
  if (next_x >= room[0].size() || next_y >= room.size() || next_x < 0 || next_y < 0)
  {
    //out of room border
    return false;
  }
  position_t next_guard_position = {next_x, next_y};

  if (obstructions.contains(next_guard_position))
  {
    //turn the guard in the right direction
    int x =  guard_direction.second * -1;
    int y = guard_direction.first * 1;
    guard_direction = {x, y};

    return do_next_step(room, obstructions, guard_position, guard_direction);
  }
  else
  {
    guard_position = next_guard_position;
  }
  return true;
}


int main() {

  const std::string input_file = "./input_data.txt";
  std::ifstream input_data(input_file);
  if (!input_data.is_open()) {
    std::cerr << "cannot find file " << input_file << std::endl;
    return 1;
  }
  long sum = 0;

  std::string text_line;

  std::vector<std::string> room;
  std::set<position_t> obstructions;
  position_t guard_position;
  direction_t guard_direction{0,-1};  //up

  while (std::getline(input_data, text_line)) {
    string_trimmer::trim(text_line);
    if (text_line.empty()) {
      break;
    }
    room.push_back(text_line);

    for (int x = 0; x < text_line.size(); ++x) {
      if (text_line[x] == '#') {
        auto insert_result = obstructions.insert(std::make_pair(x, room.size()-1));
        if (!insert_result.second) {
          std::cerr << "cannot insert " << x << std::endl;
          return 1;
        }
      }
      else if (text_line[x] == '^') {
        guard_position.first = x;
        guard_position.second = static_cast<int>(room.size()-1);
      }
    }
  }

  input_data.close();

  std::set<position_t> guard_positions;
  guard_positions.insert(guard_position);

  while( do_next_step(room, obstructions, guard_position, guard_direction) )
  {
    guard_positions.insert(guard_position);
  }

  std::cout << "Solution: " << guard_positions.size() << std::endl;
  return 0;
}
