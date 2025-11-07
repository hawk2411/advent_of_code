#include <fstream>
#include <iostream>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "room.h"

using position_t = std::pair<int, int>;
using direction_t = std::pair<int, int>;
/*
 *How to find loops
  When the guard visits a new position, it must be checked by placing an imaginary obstacle whether he will
  ever return to that position.
*/


//std::optional<position_t> get_next_obstacle_position(const std::vector<std::string>& room, const std::set<position_t>& obstructions, const guard_t& guard_position)
//{
//  int next_x = guard_position.position.first + guard_position.direction.first;
//  int next_y = guard_position.position.second + guard_position.direction.second;
//  if (next_x >= room[0].size() || next_y >= room.size() || next_x < 0 || next_y < 0)
//  {
//    //out of room border
//    return {};
//  }
//  position_t obstacle = {next_x, next_y};
//
//  if (obstructions.contains(obstacle))
//  {
//    //turn the guard to the right
//    guard_t turn_right {guard_position};
//    turn_right.turn_right();
//    return get_next_obstacle_position(room, obstructions, turn_right);
//  }
//  return obstacle;
//}
//
//std::optional<position_t> do_next_step(const std::vector<std::string>& room, const std::set<position_t>& obstructions, const position_t& guard_position, direction_t& guard_direction) {
//  int next_x = guard_position.first + guard_direction.first;
//  int next_y = guard_position.second + guard_direction.second;
//  if (next_x >= room[0].size() || next_y >= room.size() || next_x < 0 || next_y < 0)
//  {
//    //out of room border
//    return {};
//  }
//  position_t next_guard_position = {next_x, next_y};
//
//  if (obstructions.contains(next_guard_position))
//  {
//    //turn the guard to the right
//    int x =  guard_direction.second * -1;
//    int y = guard_direction.first * 1;
//    guard_direction = {x, y};
//
//    return do_next_step(room, obstructions, guard_position, guard_direction);
//  }
//  return next_guard_position;
//}
//
//bool is_loop(const std::vector<std::string>& room, const std::set<position_t>& obstacles, const std::optional<position_t>& start_postion, const position_t& guard_position, const direction_t& direction) {
//
//  direction_t virt_direction = {direction.first, direction.second};
//
//  std::set<guard_t> guard_positions;
//
//  auto next_position = do_next_step(room, obstacles, guard_position, virt_direction);
//  while(next_position.has_value()) {
//    if(next_position.value() == start_postion) {
//      return true;
//    }
//    next_position = do_next_step(room, obstacles, next_position.value(), virt_direction);
//  }
//  //guard is out of bounds
//  return false;
//}

int main() {
    const std::string input_file = "./input_data.txt";
    std::ifstream input_data(input_file);
    if (!input_data.is_open()) {
        std::cerr << "cannot find file " << input_file << std::endl;
        return 1;
    }
    long sum = 0;

    std::string text_line;

    auto room = Room::Create(input_data);
    if (room == nullptr) {
        std::cerr << "cannot open file " << input_file << std::endl;
        return 1;
    }

    input_data.close();

    int count_loops = 0;


    //here we check if is possible to place an obstacle in front of guard
    auto next_possible_guard_position = room->GetNextPossibleGuardPosition(room->GetGuard());

    while (next_possible_guard_position.has_value()) {
        std::cout << "Obstacle position: " << next_possible_guard_position.value().GetPosition().X() << " " << next_possible_guard_position.value().GetPosition().Y() <<'\n';
        Room try_room = *room;
        //place the obstacle and let the guard runs again it
        if (!try_room.PlaceObstruction(next_possible_guard_position.value().GetPosition())) {
            std::cerr << "cannot place obstruction" << std::endl;
            return 1;
        }
        //now we let guard continue his patrol. If he goes out of bounds then we have no loop but
        //if he comes back to guard_position then we have a loop
        if (try_room.IsGuardInLoop()) {
            ++count_loops;
            std::cout << "Found a loop. Current count: " << count_loops << std::endl;
        }
        room->PlaceGuard(next_possible_guard_position.value());
        next_possible_guard_position = room->GetNextPossibleGuardPosition(next_possible_guard_position.value());
    }

    std::cout << "Solution: " << count_loops << std::endl;
    return 0;
}
