add_library(inheritance-cpp-library source.cpp header.hpp)
target_include_directories(inheritance-cpp-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(inheritance-cpp main.cpp)
target_link_libraries(inheritance-cpp LINK_PUBLIC inheritance-cpp-library)
