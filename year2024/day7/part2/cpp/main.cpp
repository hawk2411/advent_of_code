#include <fstream>
#include <iostream>
#include <string>
#include <trim_functions.h>
#include <vector>

struct dataRow_t {
  unsigned long sum {0};
  std::vector<unsigned long> numbers;
};

std::vector<dataRow_t> test_data;

int bits_needed(unsigned int n) { return std::bit_width(n == 0 ? 1u : n); }

unsigned long do_func(unsigned long left, unsigned long right, char operand) {
  if (operand == '0') {
    return left + right;
  }
  return left * right;
}

int main() {

  const std::string input_file = "./input_data.txt";
  std::ifstream input_data(input_file);
  if (!input_data.is_open()) {
    std::cerr << "cannot find file " << input_file << std::endl;
    return 1;
  }
  unsigned long sum = 0;

  std::string text_line;

  while (std::getline(input_data, text_line)) {
    string_trimmer::trim(text_line);

    if (text_line.empty()) {
      break;
    }
    auto pos = text_line.find(':');
    if (pos == std::string::npos) {
      std::cerr << "The input file has a wrong format\n";
      input_data.close();
    }
    auto sumstr = text_line.substr(0, pos);
    auto result = string_functions::split(text_line.substr(pos + 1), " ");
    dataRow_t data;
    data.sum = std::stol(sumstr);
    for (const auto &numberstr : result) {
      data.numbers.push_back(std::stol(numberstr));
    }

    test_data.push_back(data);
  }

  input_data.close();

  std::cout << "Solution: " << sum << std::endl;
  return 0;
}
