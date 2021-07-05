/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"
#include <thread>

void function_1() {
    std::cout << "Beauty is only skin deep" << std::endl;
}

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    std::thread t1(function_1);     // t1 starts running
    
    // can only join or detach a thread only once.
    // t1.join();                   // main thread waits for t1 to return
    //t1.detach();                    // t1 will run freely on its own - daemon process
    
    if (t1.joinable()) {
        t1.join();
        std::cout << "Joined thread t1\n";
    } else {
        std::cout << "Cannot join\n";
    }
    
    return EXIT_SUCCESS;
}

 
