set(PROJECT_TITLE "My-CLI-Playground")
set(CMAKE_VERSION "3.18")

set(C_STANDARD "11") # C11
set(CXX_STANDARD "20") # C++20
set(CFLAGS "-Wall -Werror -pedantic-errors")

set(DIR_INCLUDE "./")

cmake_minimum_required(VERSION "${CMAKE_VERSION}")

set(CMAKE_C_STANDARD ${C_STANDARD})
set(CMAKE_CXX_STANDARD ${CXX_STANDARD})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CFLAGS})

project(${PROJECT_TITLE})
include_directories(${DIR_INCLUDE})

add_subdirectory(./stackqueue-c)
add_subdirectory(./spiralmatrix-cpp)
add_subdirectory(./symbolic-to-octal-c)
add_subdirectory(./blocks-c)

add_subdirectory(./testbench-objcpp)
add_subdirectory(./testbench-objc)
add_subdirectory(./testbench-cpp)
add_subdirectory(./testbench-c)
add_subdirectory(./chicken-egg-cpp)
