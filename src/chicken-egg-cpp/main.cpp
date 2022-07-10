/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

#include "header.hpp"
#include <array>

void *operator new(std::size_t size) {
    std::cout << "called operator new" << std::endl;
    return std::malloc(size);
}

void operator delete(void *arg) noexcept {
    std::cout << "called operator delete" << std::endl;
    return std::free(arg);
}

/*!
    \brief      Program execution begins here.
    
    \param[in]  argc    Command line argument count
    \param[in]  argv    Command line arguments

    \return     0 on success, non-zero on failure
 */
int main(int argc, const char *argv[]) {
    auto hen = chicken::mother_chicken();
    auto penguin_mom = penguin::mother_penguin();
   
    constexpr auto batch_size = 5;
    auto egg_batch = std::array<std::unique_ptr<egg>, batch_size>();

    egg_batch[0] = hen->lay_egg();
    egg_batch[1] = hen->lay_egg();
    egg_batch[2] = hen->lay_egg();
    egg_batch[3] = penguin_mom->lay_egg();
    egg_batch[4] = penguin_mom->lay_egg();
    
    std::for_each(egg_batch.begin(), 
                  egg_batch.end(), 
                  [](const std::unique_ptr<egg> &egg){
                      egg->hatch();
                  });
 
    return EXIT_SUCCESS;
}

