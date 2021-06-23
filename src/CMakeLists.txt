set(PROJECT_TITLE "My-CLI-Playground")
set(CMAKE_VERSION "3.18")

set(CXX_STD "20") # C11
set(CFLAGS "-Wall -Werror -pedantic-errors")

set(DIR_INCLUDE "./")

cmake_minimum_required(VERSION "${CMAKE_VERSION}")

set(CMAKE_CXX_STANDARD "${CXX_STD}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CFLAGS}")

project("${PROJECT_TITLE}")
include_directories("${DIR_INCLUDE}")

add_subdirectory("./stackqueue-c")
add_subdirectory(./spiralmatrix-cpp)
