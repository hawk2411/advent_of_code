set(day "3")
set(part "1")
#include(${CMAKE_SOURCE_DIR}/target.cmake)
configure_file(../../input_data.txt ${CMAKE_BINARY_DIR}/year${current_year}/day${day}/part${part}/cpp/input_data.txt COPYONLY)
configure_file(../../test_data.txt ${CMAKE_BINARY_DIR}/year${current_year}/day${day}/part${part}/cpp/test_data.txt)
set(target year${current_year}_day${day}_part${part})

add_executable(${target} main.cpp)
target_link_libraries(${target}
        PUBLIC
        global_lib)
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/global_inc)
