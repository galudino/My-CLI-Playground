/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"
#include <fstream>

constexpr auto csv_filepath = "../../../../dat/csv/noble_gases.csv";

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    auto infile = std::ifstream(csv_filepath);
    
    if (!infile) {
        std::cerr << "Unable to open " << csv_filepath << std::endl;
        return EXIT_FAILURE;
    }
   
    auto bytes = std::vector<char>(std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>());
    
    infile.close();
    
    for (const auto byte : bytes) {
        std::cout << byte;
    }
    
    return EXIT_SUCCESS;
}

