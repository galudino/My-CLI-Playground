add_library(symbolic-to-octal-c-library source.c header.h)
target_include_directories(symbolic-to-octal-c-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(symbolic-to-octal-c main.c)
target_link_libraries(symbolic-to-octal-c LINK_PUBLIC symbolic-to-octal-c-library)

