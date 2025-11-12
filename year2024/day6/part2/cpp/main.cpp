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

  std::set<Position> obstructions;

  // here we check if is possible to place an obstacle in front of guard
  auto next_possible_guard_position =
      room->GetNextPossibleGuardPosition(room->GetGuard());

  while (next_possible_guard_position.has_value()) {
    std::cout << "Obstacle position: "
              << next_possible_guard_position.value().GetPosition().X() << " "
              << next_possible_guard_position.value().GetPosition().Y() << '\n';
    Room try_room = *room;
    // place the obstacle and let the guard runs again it
    if (!try_room.PlaceObstruction(
            next_possible_guard_position.value().GetPosition())) {
      std::cerr << "cannot place obstruction" << std::endl;
      return 1;
    }
    // now we let guard continue his patrol. If he goes out of bounds then we
    // have no loop but if he comes back to guard_position then we have a loop
    if (try_room.IsGuardInLoop()) {
      auto insert_result =
          obstructions.insert(next_possible_guard_position->GetPosition());
      if (!insert_result.second) {
        std::cout << "cannot insert obstruction: X: "
                  << next_possible_guard_position->GetPosition().X()
                  << " Y: " << next_possible_guard_position->GetPosition().Y()
                  << "\n";
      } else {

        std::cout << "Found a loop. Current count: " << obstructions.size()
                  << "\n";
      }
    }
    room->PlaceGuard(next_possible_guard_position.value());
    next_possible_guard_position = room->GetNextPossibleGuardPosition(
        next_possible_guard_position.value());
  }

  std::cout << "Solution: " << obstructions.size() << std::endl;
  return 0;
}
