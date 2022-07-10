/*!
    \file       source.cpp
    \brief      Source file

    \author
    \date
 */

#include "header.hpp"

auto buffer::operator=(const buffer &b) -> buffer & {
    delete[] m_start;
    
    m_start = new char[b.capacity()];
    m_finish = m_start + b.size();
    m_end_of_storage = m_start + b.capacity();
    
    std::copy(b.m_start, b.m_finish, m_start);
    
    return *this;
}

auto buffer::operator=(buffer &&b) -> buffer & {
    delete[] m_start;
    
    m_start = std::exchange(b.m_start, nullptr);
    m_finish = std::exchange(b.m_finish, nullptr);
    m_end_of_storage = std::exchange(b.m_end_of_storage, nullptr);
    
    return *this;
}

auto operator<<(std::ostream &os, const buffer &b) -> std::ostream & {
    os << '[';
    std::copy(b.m_start, 
              b.m_finish, 
              std::ostream_iterator<buffer::value_type>(os, " ")); 
    os << "]\n(size: " << b.size() << " :: capacity: " << b.capacity() << ")\n";
    return os;
}

