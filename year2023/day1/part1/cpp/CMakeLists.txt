set(day "1")
set(part "1")
include(${CMAKE_SOURCE_DIR}/target.cmake)

add_executable(${target} main.cpp input_parser.cpp input_parser.h)
target_link_libraries(${target}
        PUBLIC
        global_lib)
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/global_inc)
