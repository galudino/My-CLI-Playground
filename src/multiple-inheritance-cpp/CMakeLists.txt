add_library(multiple-inheritance-cpp-library source.cpp header.hpp)
target_include_directories(multiple-inheritance-cpp-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(multiple-inheritance-cpp main.cpp)
target_link_libraries(multiple-inheritance-cpp LINK_PUBLIC multiple-inheritance-cpp-library)
