## CMake example (https://cmake.org/examples/)

The following example demonstrates some key ideas of CMake.<br>
Make sure that you have CMake installed prior to running this example.

There are three directories involved.<br>
The top level directory has two subdirectories called `./Demo` and `./Hello`.<br> 

In the directory `./Hello`, a library is built.<br>
In the directory `./Demo`, an executable is built by linking to the library.<br>

A total of three `CMakeLists.txt` files are created: one for each directory.<br>

The first, top-level directory contains the following `CMakeLists.txt` file.

```cmake
# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required(VERSION "2.8.11")
project("HelloCMake")

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory("Hello")
add_subdirectory("Demo")
```

Then for each subdirectory specified,<br>
`CMakeLists.txt` files are created. 

In the `./Hello` directory, the following `CMakeLists.txt` file is created:

```cmake
# Create a library called "Hello" which includes the source file "hello.cpp".
# The extension is already found. Any number of sources could be listed here.
add_library("Hello" "hello.cpp")

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories("Hello" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

Finally, in the `./Demo` directory,<br>
the third and final `CMakeLists.txt` file is created:

```cmake
# Add executable called "helloDemo" that is built from the source files
# "demo.cpp" and "demo_b.cpp". The extensions are automatically found.
add_executable("helloDemo" "demo.cpp" "demo_b.cpp")

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries("helloDemo" LINK_PUBLIC "Hello")
```
