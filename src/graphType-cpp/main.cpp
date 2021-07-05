/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "graphType.hpp"
#include <iostream>
#include <sstream>

void read_output_no_sentinels();

/*!
    \brief      Program execution begins here.

    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    auto g = graphType();
    
    constexpr auto path = "./src/graphType-cpp/fig_20-6.txt";
    //constexpr auto path = "./src/graphType-cpp/fig_20-17-a.txt";
    //constexpr auto path = "./src/graphType-cpp/fig_20-17-b.txt";
    //constexpr auto path = "./src/graphType-cpp/fig_20-18-a.txt";
    //constexpr auto path = "./src/graphType-cpp/fig_20-18-b.txt";
    g.createGraph(path);

    g.printGraph();

    g.depthFirstTraversal();
    g.breadthFirstTraversal();
    
    return 0;
}

