set(day "6")
set(part "2")
include(${CMAKE_SOURCE_DIR}/target.cmake)

add_executable(${target} main.cpp room.h room.cpp guard.h guard.cpp)
target_link_libraries(${target}
        PUBLIC
        global_lib)
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/global_inc)
