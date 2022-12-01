cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)


configure_file(../../input_data.txt ${CMAKE_BINARY_DIR}/day8/part2/cpp/input_data.txt)
add_executable(day8_part2 main.cpp input_parser.cpp input_parser.h unique_sequences.cpp unique_sequences.h)

target_link_libraries(day8_part2 global_lib)