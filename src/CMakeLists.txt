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
add_subdirectory(./chicken-egg-cpp)
add_subdirectory(./testbench-c)
add_subdirectory(./nrvo-cpp)
add_subdirectory(./testbench-objc)
add_subdirectory(./testbench-objcpp)
add_subdirectory(./graph-cpp)
add_subdirectory(./polymorphism-cpp)
add_subdirectory(./timestamp-cpp)
add_subdirectory(./threads-cpp)
add_subdirectory(./student_grade-cpp)
add_subdirectory(./graphType-cpp)
add_subdirectory(./weightedGraphType-cpp)
add_subdirectory(./msTreeType-cpp)
add_subdirectory(./testbench-cpp)
add_subdirectory(./htable-test)
#add_subdirectory(./opengl-test-cpp)
add_subdirectory(./sfml-test-cpp)
add_subdirectory(./inheritance-cpp)
add_subdirectory(./multiple-inheritance-cpp)

add_subdirectory(./fork-dirent-c)
add_subdirectory(./threads-c)

add_subdirectory(./csv-cpp)
