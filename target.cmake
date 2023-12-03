configure_file(../../input_data.txt ${CMAKE_BINARY_DIR}/year${current_year}/day${day}/part${part}/cpp/input_data.txt COPYONLY)
set(target year${current_year}_day${day}_part${part})
