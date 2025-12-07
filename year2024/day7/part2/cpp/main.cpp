#include <fstream>
#include <iostream>
#include <string>
#include <trim_functions.h>
#include <vector>

struct dataRow_t {
  unsigned long sum{0};
  std::vector<unsigned long> numbers;
};

std::vector<dataRow_t> test_data;

const std::string operators{"+*|"};

unsigned long do_func(unsigned long left, unsigned long right, char operand) {

  unsigned long result{0};
  switch (operand) {
  case '+':
    result = left + right;
    break;
  case '*':
    result = left * right;
    break;
  default: {
    result = std::stol(std::to_string(left) + std::to_string(right));
  } break;
  }
  return result;
}

void gen(const std::string &functions, const dataRow_t &data, unsigned long &sum, bool& found) {
  if(found ) {
    return;
  }
  if (functions.size() == data.numbers.size() - 1) {
    auto left = data.numbers.at(0);
    for (int i = 1; i < data.numbers.size(); ++i) {
      left = do_func(left, data.numbers[i], functions[i - 1]);
    }
    if (left == data.sum) {
      found = true;
      sum += left;
    }
    return;
  }
  for (const auto ch : operators) {
    if( found ) {
      break;
    }
    gen(functions + ch, data, sum, found);

  }
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
    for (const auto &number_string : result) {
      data.numbers.push_back(std::stol(number_string));
    }

    test_data.push_back(data);
  }

  input_data.close();
  for (const auto &data : test_data) {
    bool found = false;
    gen("", data, sum, found);
  }

  std::cout << "Solution: " << sum << std::endl;
  return 0;
}
