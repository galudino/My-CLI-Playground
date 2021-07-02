/*!
    \file       source.cpp
    \brief      Source file

    \author
    \date
 */

#include "header.hpp"
#include <cmath>

template <typename P, typename Q>
std::ostream &operator<<(std::ostream &os, const std::pair<P, Q> &p) {
    os << "{" << p.first << ", " << p.second << "}";
    return os;
}

void shape2::draw() {
    std::cout << "Drawing shape at position {" << x() << ", " << y() << "}\n";
}

void rect2::draw() {
    /*
    auto str = std::string();

    for (auto i = 0; i < length(); i++) {
        str += '-';
    }
    str += '\n';

    for (auto i = 0; i < width(); i++) {
        str += '|';
        for (auto j = 0; j < length() - 2; j++) {
            str += ' ';
        }
        str += "|\n";
    }

    for (auto i = 0; i < length(); i++) {
        str += '-';
    }
    str += '\n';

    std::cout << str;
    */
    shape2::draw();
    std::cout << "rect2::draw()" << std::endl;
}

float rect2::area() {
    return length() * width();
}

void eqtri2::draw() {
    shape2::draw();
    std::cout << "eqtri2::draw()" << std::endl;
}

float eqtri2::area() {
    return (std::cbrt(3) / 4) * (side() * side());
}
