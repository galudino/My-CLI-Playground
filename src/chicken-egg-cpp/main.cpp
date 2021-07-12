/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"
#include <array>

/*
void *operator new(std::size_t size) {
    std::cout << "called operator new" << std::endl;
    return std::malloc(size);
}

void operator delete(void *arg) noexcept {
    std::cout << "called operator delete" << std::endl;
    return std::free(arg);
}
*/

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    auto c = std::make_unique<chicken>();
    auto p = std::make_unique<penguin>();
    
    auto egg_batch = std::array<std::unique_ptr<egg>, 5>();

    egg_batch[0] = c->lay_egg();
    egg_batch[1] = c->lay_egg();
    egg_batch[2] = p->lay_egg();
    egg_batch[3] = c->lay_egg();
    egg_batch[4] = p->lay_egg();
    
    for (const auto &egg : egg_batch) {
        egg->hatch();
    }
 
    return EXIT_SUCCESS;
}

