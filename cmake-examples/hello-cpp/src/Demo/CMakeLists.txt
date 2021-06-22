set(CXX_STD "20") # C11
set(CFLAGS "-Wall -Werror -pedantic-errors")

set(CMAKE_CXX_STANDARD "${CXX_STD}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CFLAGS}")

include_directories("../MyTemplate")

# Add executable called "helloDemo" that is built from the source files
# "demo.cpp" and "demo_b.cpp". The extensions are automatically found.
add_executable("helloDemo" "demo.cpp" "demo_b.cpp")

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
#target_link_libraries("helloDemo" LINK_PUBLIC "Hello")

target_link_libraries("helloDemo" INTERFACE "Template")
target_link_libraries("helloDemo" LINK_PUBLIC "Hello")
