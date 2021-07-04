/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"

#include <iostream>
#include <fstream>
#include <array>

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    student s("./src/student_grade-cpp/test.txt");
    
    auto output_file = std::ofstream();
    output_file.open("./src/student_grade-cpp/testavg.out");
    
    output_file << s; 
    output_file.close();
    
    std::cout << s << '\n';

    return EXIT_SUCCESS;
}

