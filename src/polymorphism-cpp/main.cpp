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
    auto rect = rect2(0, 0, 3, 7);

    std::cout << &rect << " has an area of " << rect.area() << std::endl;

    rect.draw();

    auto eqtri = eqtri2(0, 0, 3);
    std::cout << &eqtri << " has an area of " << eqtri.area() << std::endl;
    
    eqtri.draw();

    return EXIT_SUCCESS;
}

