set(day "3")
set(part "2")
include(${CMAKE_SOURCE_DIR}/target.cmake)

add_executable(${target} main.cpp)
target_link_libraries(${target}
        PUBLIC
        global_lib)
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/global_inc)
