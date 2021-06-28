/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"
#include <array>

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    chicken c;
    penguin p;
    
    std::array<egg *, 5> egg_batch;

    egg_batch[0] = c.lay_egg();
    egg_batch[1] = c.lay_egg();
    egg_batch[2] = p.lay_egg();
    egg_batch[3] = c.lay_egg();
    egg_batch[4] = p.lay_egg();
    
    for (const auto &egg : egg_batch) {
        egg->hatch();
    }
 
    return EXIT_SUCCESS;
}

