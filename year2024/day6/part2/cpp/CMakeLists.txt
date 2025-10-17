set(day "6")
set(part "2")
include(${CMAKE_SOURCE_DIR}/target.cmake)
message("halle ${CMAKE_SOURCE_DIR}")
add_compile_options(-fmodules -fsearch-include-path bits/std.cc)

add_executable(${target} main.cpp)
target_link_libraries(${target}
        PUBLIC
        global_lib)
target_compile_options(${target} PRIVATE -fmodules -fsearch-include-path bits/std.cc)
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/global_inc)
