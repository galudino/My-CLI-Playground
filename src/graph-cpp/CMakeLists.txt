add_library(graph-cpp-library header.hpp source.cpp)
target_include_directories(graph-cpp-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(graph_template-cpp-library INTERFACE graph.hpp graph_impl.hpp)
target_include_directories(graph_template-cpp-library INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(graph-cpp main.cpp)
target_link_libraries(graph-cpp LINK_PUBLIC graph-cpp-library)
target_link_libraries(graph-cpp INTERFACE graph_template-cpp-library)
