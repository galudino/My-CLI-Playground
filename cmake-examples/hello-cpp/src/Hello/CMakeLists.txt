# Create a library called "Hello" which includes the source file "hello.cpp".
# The extension is already found. Any number of sources could be listed here.
add_library("Hello" "hello.hpp" "hello.cpp")
## Note: Also providing "hello.hpp" so IDEs will recognize that it exists.

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories("Hello" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
