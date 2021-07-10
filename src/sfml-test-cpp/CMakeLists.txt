add_library(sfml-test-cpp-library source.cpp header.hpp)
target_include_directories(sfml-test-cpp-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(sfml-test-cpp main.cpp)
target_link_libraries(sfml-test-cpp LINK_PUBLIC sfml-test-cpp-library)
