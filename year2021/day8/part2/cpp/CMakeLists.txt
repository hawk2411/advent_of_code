set(day "8")
set(part "2")
include(${CMAKE_SOURCE_DIR}/year2021/year.cmake)

add_executable(${target} main.cpp input_parser.cpp input_parser.h unique_sequences.cpp unique_sequences.h)
target_link_libraries(${target}
        PUBLIC
        global_lib)
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/global_inc)
