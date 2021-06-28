add_library(testbench-objc-library source.m header.h)
target_include_directories(testbench-objc-library PUBLIC )
add_executable(testbench-objc main.m)
target_link_libraries(testbench-objc LINK_PUBLIC testbench-objc-library -framework Foundation -framework Cocoa -framework AppKit -framework CoreData)
