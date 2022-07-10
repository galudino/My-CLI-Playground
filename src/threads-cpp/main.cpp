/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"
#include <thread>
#include <vector>
#include <array>

int shared_data = 0;
std::mutex shared_data_mutex;

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    // We know we want 16 total threads,
    // so an array is adequate.
    auto v = std::array<std::thread, 16>();
    
    // Spawn all 16 threads.
    // Each thread will add (i + 1) to shared_data.
    for (auto i = 0; i < 16; i++) {
        v[i] = std::thread([i](void) -> void {
            // mutex ensures that only one thread
            // can write to shared_data at a time.
            shared_data_mutex.lock(); 
            shared_data += (i + 1);
            shared_data_mutex.unlock();
        });
    }
    
    // Join all threads
    for (auto &t : v) {
        t.join();
    }
    
    // shared_data should be 136
    std::cout << "Final sum: " << shared_data << std::endl;
      
    auto thr = std::thread([](int i, int j, int k) -> int {
        shared_data_mutex.lock();
        shared_data += (i + j + k);
        shared_data_mutex.unlock();
        return shared_data;
    }, 10, 20, 30);

    thr.join();
    std::cout << shared_data << std::endl;

    return EXIT_SUCCESS;
}

 
