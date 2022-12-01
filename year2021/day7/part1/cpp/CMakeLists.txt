set(day "7")
set(part "1")
include(${CMAKE_SOURCE_DIR}/year2021/year.cmake)

add_executable(${target} main.cpp input_parser.cpp input_parser.h)
