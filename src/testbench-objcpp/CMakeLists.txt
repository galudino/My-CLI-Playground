add_library(testbench-objcpp-library source.mm header.h)
target_include_directories(testbench-objcpp-library PUBLIC )
add_executable(testbench-objcpp main.mm)
target_link_libraries(testbench-objcpp LINK_PUBLIC testbench-objcpp-library -framework Foundation -framework Cocoa -framework AppKit -framework CoreData)
