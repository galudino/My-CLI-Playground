find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(opengl-test-cpp-library source.cpp header.hpp)
target_include_directories(opengl-test-cpp-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(opengl-test-cpp-library
    LINK_PUBLIC 
        glfw 
        OpenGL::GL
)

add_executable(opengl-test-cpp main.cpp)

target_link_libraries(opengl-test-cpp 
    LINK_PUBLIC 
        opengl-test-cpp-library 
)

