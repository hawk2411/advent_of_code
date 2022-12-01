set(day "4")
set(part "1")
include(${CMAKE_SOURCE_DIR}/year2021/year.cmake)

add_executable(${target} main.cpp BingoBoard.cpp)