/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "weightedGraphType.hpp"
#include <iostream>

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    auto wg = weightedGraphType();
    
    constexpr auto path = "./src/weightedGraphType-cpp/fig_20-7.txt";
    //constexpr auto path = "./src/weightedGraphType-cpp/fig_20-19.txt";
    ///constexpr auto path = "./src/weightedGraphType-cpp/fig_20-20.txt";
    wg.createWeightedGraph(path);

    if (wg.isEmpty()) {
        std::cout << "Graph is empty - check input file" << std::endl;
        return -1;
    }
    
    wg.printGraph();
    wg.printWeightMatrix();
    wg.shortestPath(0);
    wg.printShortestDistance(0);

    return EXIT_SUCCESS;
}

