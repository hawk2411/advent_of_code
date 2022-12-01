cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)

configure_file(../../input_data.txt ${CMAKE_BINARY_DIR}/day8/part1/cpp/input_data.txt)
add_executable(day8_part1 main.cpp input_parser.cpp input_parser.h)

target_link_libraries(day8_part1
        PUBLIC
        global_lib)
target_include_directories(day8_part1 PUBLIC ${CMAKE_SOURCE_DIR}/global_inc)