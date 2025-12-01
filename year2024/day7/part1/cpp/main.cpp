#include <fstream>
#include <iostream>
#include <string>
#include <trim_functions.h>

int main() {

  const std::string input_file = "./input_data.txt";
  std::ifstream input_data(input_file);
  if (!input_data.is_open()) {
    std::cerr << "cannot find file " << input_file << std::endl;
    return 1;
  }
  long sum = 0;

  std::string text_line;

  while (std::getline(input_data, text_line)) {
    string_trimmer::trim(text_line);
    if (text_line.empty()) {
      break;
    }
  }

  input_data.close();

  std::cout << "Solution: " << std::endl;
  return 0;
}
