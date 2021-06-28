add_library(testbench-cpp-library source.cpp header.hpp)
target_include_directories(testbench-cpp-library PUBLIC )
add_executable(testbench-cpp main.cpp)
target_link_libraries(testbench-cpp LINK_PUBLIC testbench-cpp-library)
