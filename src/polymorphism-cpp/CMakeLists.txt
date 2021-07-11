add_library(polymorphism-cpp-library source.cpp header.hpp)
target_include_directories(polymorphism-cpp-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(polymorphism-cpp main.cpp)
target_link_libraries(polymorphism-cpp LINK_PUBLIC polymorphism-cpp-library)
