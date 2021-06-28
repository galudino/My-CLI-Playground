add_library(chicken-egg-cpp-library source.cpp header.hpp)
target_include_directories(chicken-egg-cpp-library PUBLIC )
add_executable(chicken-egg-cpp main.cpp)
target_link_libraries(chicken-egg-cpp LINK_PUBLIC chicken-egg-cpp-library)
