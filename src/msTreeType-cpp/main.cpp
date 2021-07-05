/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "msTreeType.hpp"
#include <iostream>

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    auto mst = msTreeType();
    
    constexpr auto path = "./src/msTreeType-cpp/fig_20-13.txt";
    //constexpr auto path = "./src/msTreeType-cpp/fig_20-21.txt";
    //constexpr auto path = "./src/msTreeType-cpp/fig_20-22.txt";
    //constexpr auto path = "./src/msTreeType-cpp/fig_20-23.txt";
    mst.createSpanningGraph(path);

    if (mst.isEmpty()) {
        std::cerr << "Graph is empty. Check input file" << std::endl;
        return -1;
    }

    mst.minimalSpanning(0);
    mst.printTreeAndWeight();

    return EXIT_SUCCESS;
}

