#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <set>
#include <string>
#include <utility>

#include "room.h"

using position_t = std::pair<int, int>;
using direction_t = std::pair<int, int>;
/*
 *How to find loops
  When the guard visits a new position, it must be checked by placing an
 imaginary obstacle whether he will ever return to that position.
*/

int main() {
  const std::string input_file = "./input_data.txt";
  std::ifstream input_data(input_file);
  if (!input_data.is_open()) {
    std::cerr << std::format("Cannot find file: '{0}'.", input_file);
    return 1;
  }

  std::string text_line;

  auto room = Room::Create(input_data);
  input_data.close();

  if (room == nullptr) {
    std::cerr << std::format("Cannot read data in file '{0}'.\n", input_file);
    return 1;
  }

  std::set<Position> obstructions;

  // here we check if is possible to place an obstacle in front of guard
  auto next_position = room->GetNextPossibleGuardPosition(room->GetGuard());

  while (next_position.has_value()) {

    std::cout << std::format("Obstacle position: {0} {1}\n",
                             next_position.value().GetPosition().X(),
                             next_position.value().GetPosition().Y());

    Room try_room = *room;
    // place the obstacle and let the guard runs again it
    if (!try_room.PlaceObstruction(next_position.value().GetPosition())) {
      std::cout << "cannot place obstruction\n";
      return 1;
    }
    // now we let guard continue his patrol. If he goes out of bounds then we
    // have no loop but if he comes back to guard_position then we have a loop
    if (try_room.IsGuardInLoop()) {
      auto insert_result = obstructions.insert(next_position->GetPosition());
      if (!insert_result.second) {
        std::cout << std::format("cannot insert obstruction: X: {0} {1}\n",
                                 next_position->GetPosition().X(),
                                 next_position->GetPosition().Y());
      } else {
        std::cout << std::format("Found a loop. Current count: {0}\n",
                                 obstructions.size());
      }
    }
    room->PlaceGuard(next_position.value());
    next_position = room->GetNextPossibleGuardPosition(next_position.value());
  }

  std::cout << std::format("Solution: {0}\n", obstructions.size());
  return 0;
}
