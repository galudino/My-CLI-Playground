/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"
#include "graph.hpp"

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    // graph takes a std::initializer_list<std::initializer_list<int>>, `list`.
    // Each element, i, in `list[i]` is an initializer_list<int>.
    // The first element in an initializer_list<int> is a vertex id -- an origin vertex.
    // Subsequent elements
    auto g = graph({
        { 0, 1, 2 },        // vertex 0 is adjacent to 1 and 2
        { 1, 0, 2, 3, 4 },  // vertex 1 is adjacent to 0, 2, 3, and 4
        { 2, 0, 1, 3 },     // vertex 2 is adjacent to 0, 1, and 2
        { 3, 1, 2, 5, 6 },  // vertex 3 is adjacent to 1, 2, 5, and 6
        { 4, 1, 6 },        // vertex 4 is adjacent to 1 and 6
        { 5, 3, 6 },        // vertex 5 is adjacent to 3 and 6
        { 6, 3, 4, 5 }      // vertex 6 is adjacent to 3, 4, and 5
    });
    

    g.print();

    g.depth_first_traversal();
    g.breadth_first_traversal();
    return 0;
}
