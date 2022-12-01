set(day "8")
set(part "1")
include(${CMAKE_SOURCE_DIR}/year2020/year.cmake)

add_executable(${target} main.cpp StringTools.cpp StringTools.h CodeLine.cpp CodeLine.h Computer.cpp Computer.h)
