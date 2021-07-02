/*!
    \file       source.cpp
    \brief      Source file

    \author
    \date
 */

#include "header.hpp"

addable &Int::operator+=(const addable &rhs) {
    auto &i = Int_cast(rhs);
    m_impl += i.m_impl;
    return *this;
}

addable &Int::operator-=(const addable &rhs) {
    auto &i = Int_cast(rhs);
    m_impl += i.m_impl;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Int &i) {
    os << i.m_impl;
    return os;
}
