add_library(testbench-objc-library source.m header.h)
target_compile_options(testbench-objc-library PUBLIC -fblocks -fobjc-arc)
target_include_directories(testbench-objc-library PUBLIC )
add_executable(testbench-objc main.m)
target_compile_options(testbench-objc-library PUBLIC -fblocks -fobjc-arc)
target_link_libraries(testbench-objc
    LINK_PUBLIC 
    testbench-objc-library 
    "-framework Foundation" 
    "-framework Cocoa" 
    "-framework AppKit"
    "-framework CoreData"
    "-framework CoreBluetooth"
    objc
)

#target_link_libraries(testbench-objc LINK_PUBLIC testbench-objc-library -framework Foundation -framework Cocoa -framework AppKit -framework CoreData)
