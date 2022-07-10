 /*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    auto b = readwritebuffer{16};

    for (auto i = 0; i < b.size(); i++) {
        b[i] = '-';
    }
    
    b.set_at(0, 'h');
    
    std::cout << b << std::endl;
    
    return EXIT_SUCCESS;
}

