#include "input_parser.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct position_cost_item {
  unsigned int position;
  unsigned int costs;
};

position_cost_item
calc_cheapest_position(const std::vector<unsigned int> &positions);

position_cost_item
check_position(unsigned int pos,
               const std::map<unsigned int, unsigned int> &crabs_positions);

unsigned int countNotIncludedChars(const std::string &search_in,
                                   const std::string &search_for) {

  unsigned int not_found_segments = 0;
  for (const auto &segment : search_for) {
    auto position = search_in.find(segment);

    not_found_segments += (position == std::string::npos) ? 1 : 0;
  }
  return not_found_segments;
}

bool isThree(const std::string &maybe_three, const std::string &one) {
  // one is completely in three
  if (maybe_three.size() != 5) {
    return false;
  }

  unsigned int not_found_segments = countNotIncludedChars(maybe_three, one);

  return (not_found_segments == 0);
}

int main() {

  std::map<std::size_t, std::vector<int>> size_to_number = {
      {2, {1}}, {3, {7}}, {4, {4}}, {5, {2, 3, 5}}, {6, {0, 6, 9}}, {7, {8}}};

  //    0:      1:      2:      3:      4:
  //     aaaa    ....    aaaa    aaaa    ....
  //    b    c  .    c  .    c  .    c  b    c
  //    b    c  .    c  .    c  .    c  b    c
  //     ....    ....    dddd    dddd    dddd
  //    e    f  .    f  e    .  .    f  .    f
  //    e    f  .    f  e    .  .    f  .    f
  //     gggg    ....    gggg    gggg    ....
  //
  //    5:      6:      7:      8:      9:
  //     aaaa    aaaa    aaaa    aaaa    aaaa
  //    b    .  b    .  .    c  b    c  b    c
  //    b    .  b    .  .    c  b    c  b    c
  //     dddd    dddd    ....    dddd    dddd
  //    .    f  e    f  .    f  e    f  .    f
  //    .    f  e    f  .    f  e    f  .    f
  //     gggg    gggg    ....    gggg    gggg

  const std::string input_file = "./input_data.txt";
  std::ifstream input_data(input_file);
  if (!input_data.is_open()) {
    std::cerr << "cannot find file " << input_file << std::endl;
    return 1;
  }
  std::string text_line;

  unsigned int sum = 0;

  while (std::getline(input_data, text_line)) {
    auto count_unique_sequences = input_parser::get_number(text_line);
    sum += count_unique_sequences;
  }

  input_data.close();

  std::cout << "Solution: " << sum << std::endl;
  return 0;
}

position_cost_item
calc_cheapest_position(const std::vector<unsigned int> &positions) {
  std::map<unsigned int, unsigned int> count_crabs_on_same_position;

  if (positions.empty())
    return {0, 0};

  for (const auto &pos : positions) {
    auto position = count_crabs_on_same_position.find(pos);
    if (position == count_crabs_on_same_position.end()) {
      count_crabs_on_same_position[pos] = 1;
    } else {
      position->second++;
    }
  }

  position_cost_item result{};
  bool first_time = true;
  auto last_position =
      count_crabs_on_same_position.rbegin()->first; // greatest position
  for (unsigned int i = 0; i <= last_position; i++) {

    position_cost_item cost = check_position(i, count_crabs_on_same_position);
    if (first_time) {
      result = cost;
      first_time = false;
    } else {
      if (result.costs > cost.costs) {
        result = cost;
      }
    }
  }

  return result;
}

position_cost_item
check_position(const unsigned int position,
               const std::map<unsigned int, unsigned int> &crabs_positions) {

  position_cost_item result = {position, 0};
  for (const auto [pos, count] : crabs_positions) {
    if (pos == position) {
      continue;
    }

    auto m = std::max(position, pos);
    auto n = std::min(position, pos);
    auto diff = m - n;
    unsigned int cost = (diff * (diff + 1)) / 2;

    result.costs += cost * count;
  }

  return result;
}
