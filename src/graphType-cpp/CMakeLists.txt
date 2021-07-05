add_library(graphType-cpp-library graphType.cpp graphType.hpp)
target_include_directories(graphType-cpp-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(graphType-cpp main.cpp)
target_link_libraries(graphType-cpp LINK_PUBLIC graphType-cpp-library)
