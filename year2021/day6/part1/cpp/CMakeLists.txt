set(day "6")
set(part "1")
include(${CMAKE_SOURCE_DIR}/year2021/year.cmake)

add_executable(${target} main.cpp input_parser.cpp input_parser.h fish_simulator.cpp fish_simulator.h)

find_package(Threads REQUIRED)
if (Threads_FOUND)
    target_link_libraries (${target} ${CMAKE_THREAD_LIBS_INIT})
endif (Threads_FOUND)
