/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <sstream>

template <typename Container>
auto operator<<(std::ostream &os, const Container &c) -> std::ostream & {
    using ContainerValue = typename Container::value_type;
    
    auto ostream_it = std::ostream_iterator<ContainerValue>(os, " ");
    std::copy(c.begin(), c.end(), ostream_it);

    return os;
}

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    auto arr = std::array<int, 3> { 1, 2, 3 };
    std::cout << arr << std::endl;

    auto sarr = std::array<std::string, 3> { "alpha", "beta", "charlie" };
    std::cout << sarr << std::endl;

    std::copy(sarr.begin(), sarr.end(), std::ostream_iterator<std::string>(std::cout, ","));

    return 0;
}

