#include "hello.hpp"
#include <iostream>

void hello::say_hello(const std::string &s) {
    std::cout << "Hello, " << s << "!" << std::endl;
}
