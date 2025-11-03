#include <fstream>
#include <iostream>
#include <optional>
#include <set>
#include <string>
#include <trim_functions.h>
#include <utility>
#include <vector>
#include <optional>

using position_t = std::pair<int, int>;
using direction_t = std::pair<int, int>;
/*
 *How to find loops
  When the guard visits a new position, it must be checked by placing an imaginary obstacle whether he will
  ever return to that position.
*/

std::optional<position_t> get_next_obstacle_position(const std::vector<std::string>& room, const std::set<position_t>& obstructions, const position_t& guard_position, const direction_t& guard_direction)
{
  int next_x = guard_position.first + guard_direction.first;
  int next_y = guard_position.second + guard_direction.second;
  if (next_x >= room[0].size() || next_y >= room.size() || next_x < 0 || next_y < 0)
  {
    //out of room border
    return {};
  }
  position_t next_guard_position = {next_x, next_y};

  if (obstructions.contains(next_guard_position))
  {
    //turn the guard to the right
    int x =  guard_direction.second * -1;
    int y = guard_direction.first * 1;
    const direction_t next_guard_direction {x, y};
    return get_next_obstacle_position(room, obstructions, guard_position, next_guard_direction);
  }
  return next_guard_position;
}

std::optional<position_t> do_next_step(const std::vector<std::string>& room, const std::set<position_t>& obstructions, const position_t& guard_position, direction_t& guard_direction) {
  int next_x = guard_position.first + guard_direction.first;
  int next_y = guard_position.second + guard_direction.second;
  if (next_x >= room[0].size() || next_y >= room.size() || next_x < 0 || next_y < 0)
  {
    //out of room border
    return {};
  }
  position_t next_guard_position = {next_x, next_y};

  if (obstructions.contains(next_guard_position))
  {
    //turn the guard to the right
    int x =  guard_direction.second * -1;
    int y = guard_direction.first * 1;
    guard_direction = {x, y};

    return do_next_step(room, obstructions, guard_position, guard_direction);
  }
  return next_guard_position;
}

bool is_loop(const std::vector<std::string>& room, const std::set<position_t>& obstacles, const std::optional<position_t>& start_postion, const position_t& guard_position, const direction_t& direction) {

  direction_t virt_direction = {direction.first, direction.second};

  auto next_position = do_next_step(room, obstacles, guard_position, virt_direction);
  while(next_position.has_value()) {
    if(next_position.value() == start_postion) {
      return true;
    }
    next_position = do_next_step(room, obstacles, next_position.value(), virt_direction);
  }
  //guard is out of bounds
  return false;
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

  int count_loops = 0;


  //here we check if is possible to place an obstacle in front of guard
  auto obstruction_position = get_next_obstacle_position(room, obstructions, guard_position, guard_direction);
  while (obstruction_position.has_value()) {
    std::cout << "Obstacle position: " << obstruction_position.value().first << " " << obstruction_position.value().second << std::endl;
    //place the obstacle and let the guard runs again it
    obstructions.insert(obstruction_position.value());
    direction_t next_guard_direction = guard_direction;
    std::cout<< "Guard position: " << guard_position.first << " " << guard_position.second << std::endl;
    std::cout << "Direction: " << guard_direction.first << " " << guard_direction.second << std::endl;
    //the guard runs again the placed obstacle this changes his direction to the right and make a step
    auto next_guard_pos =  do_next_step(room, obstructions, guard_position, next_guard_direction);
    if(!next_guard_pos.has_value()) {
      break;
    }
    //now we let guard continue his patrol. If he goes out of bounds then we have no loop but
    //if he comes back to guard_position then we have a loop
    if( is_loop(room, obstructions, guard_position, next_guard_pos.value(), next_guard_direction) ) {
      ++count_loops;
      std::cout << "Found a loop. Current count: " << count_loops << std::endl;

    }
    //remove virtual obstacle
    obstructions.erase(obstruction_position.value());

    //and let the guard go his normal way
    next_guard_pos =  do_next_step(room, obstructions, guard_position, guard_direction);
    if(next_guard_pos.has_value()) {
      guard_position = next_guard_pos.value();
      obstruction_position = get_next_obstacle_position(room, obstructions, guard_position, guard_direction);
    }
    else {
      obstruction_position = {};
    }
  }

  std::cout << "Solution: " << count_loops << std::endl;
  return 0;
}
