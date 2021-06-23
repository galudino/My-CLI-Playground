/*!
    \file       main.cpp
    \brief      Spiral matrix program

    \details    Given an input integer, N, create an (N * N) spiral matrix.
                For example, for N = 5, create
                    25 24 23 22 21
                    10  9  8  7 20
                    11  2  1  6 19
                    12  3  4  5 18
                    13 14 15 16 17
                Then, output the resulting spiral matrix.

                Preconditions: N > 0 && N is odd

    \author     Gem Aludino
    \date       31 Mar 2021   
 */

#include "matrix.hpp"   // required for gem::square_matrix<T, N>

#include <iostream>     // required for std::cout, std::ostream

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    // Dimension of square matrix.
    // Hard-coded for use with std::array<T, N> (stack-based array).
    constexpr auto N = 5;
    
    auto sq_mtx = gem::square_matrix<int, N>();

    if (gem::is_odd(N) && N > 0) {
        std::cout << "Spiral matrix was " << 
        (gem::spiralify(sq_mtx) 
        ? "created successfully.\n" : "not created successfully.\n") << std::endl;
    } else {
        std::cerr << "N must be greater than 0 and odd. (entered: " << N << ")" << std::endl;
    }

    std::cout << sq_mtx << std::endl; 

    return EXIT_SUCCESS;
}
