#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <exception>

class timestamp {
public:
    timestamp(auto hr = 0, auto min = 0, auto sec = 0) {}
    
    auto hr() const -> uint16_t { return m_hr; }
    auto min() const -> uint16_t { return m_min; }
    auto sec() const -> uint16_t { return m_sec; }
private:
    uint16_t m_hr;
    uint16_t m_min;
    uint16_t m_sec;
};

#endif /* HEADER_HPP */

