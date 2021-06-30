/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"

namespace ds {

template <typename T>
class graph;

}

template <typename T, size_t RowColCount = 16>
class ds::graph {
public:
    using adjmtx_row = std::array<bool, RowColCount>;
    using value_type = T;
private:
    std::array<adjmtx_row, max_count> m_adjacency_matrix;
    std::array<value_type, max_count> m_node_data;
};

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    
    return 0;
}
