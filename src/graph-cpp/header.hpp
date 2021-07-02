/*!
    \file       header.hpp
    \brief      Header file

    \author
    \date
 */

#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <forward_list>
#include <memory>
#include <algorithm>
#include <functional>
#include <exception>

struct addable {
    virtual addable &operator+=(const addable &rhs) = 0;
    virtual addable &operator-=(const addable &rhs) = 0;

    virtual ~addable() {}
};

class Int : public addable {
public:
    Int(int value = 0) : m_impl(value) {}
    
    addable &operator+=(const addable &rhs);
    addable &operator-=(const addable &rhs);
    
    void func() {}
    
    friend std::ostream &operator<<(std::ostream &os, const Int &i);
private:
    constexpr Int &Int_cast(const addable &rhs) {
        const Int *result = nullptr;
        if (!(result = dynamic_cast<const Int *>(&rhs))) {
            throw std::bad_cast();
        }
        
        return *const_cast<Int *>(result);
    }
    
    int m_impl;
};


#endif /* HEADER_HPP */

