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

  std::set<Position> guard_positions;
  guard_positions.insert(room->GetGuard().GetPosition());

  // here we check if is possible to place an obstacle in front of guard
  auto next_possible_guard_position =
      room->GetNextPossibleGuardPosition(room->GetGuard());

  while (next_possible_guard_position.has_value()) {

    std::cout << std::format(
        "Next possible guard_position : {0} {1}\n",
        next_possible_guard_position.value().GetPosition().X(),
        next_possible_guard_position.value().GetPosition().Y());

    guard_positions.insert(next_possible_guard_position.value().GetPosition());
    room->PlaceGuard(next_possible_guard_position.value());
    next_possible_guard_position = room->GetNextPossibleGuardPosition(
        next_possible_guard_position.value());
  }

  std::cout << std::format("Solution: {0}\n", guard_positions.size());
  return 0;
}
