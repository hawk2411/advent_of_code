set(day "9")
set(part "1")
include(${CMAKE_SOURCE_DIR}/year2022/year.cmake)

add_executable(${target} main.cpp)
target_link_libraries(${target}
        PUBLIC
        global_lib)
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/global_inc)
