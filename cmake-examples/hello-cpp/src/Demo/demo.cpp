#include "hello.hpp"
#include "template.hpp"

#include <iostream>

extern std::string name;

int main(int argc, const char *argv[]) {
    hello::say_hello(name);
    std::cout << "Norm of vector [3, 4] is " << tmpl::euclidean_distance({3, 4}) << std::endl;
    return 0;
}
