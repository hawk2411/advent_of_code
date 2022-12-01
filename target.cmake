cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

configure_file(../../input_data.txt ${CMAKE_BINARY_DIR}/year${current_year}/day${day}/part${part}/cpp/input_data.txt)
set(target year${current_year}_day${day}_part${part})
