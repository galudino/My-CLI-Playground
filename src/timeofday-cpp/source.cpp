/*!
    \file       source.cpp
    \brief      Source file

    \author
    \date
 */

#include "header.hpp"

timevals timevals::sentinel_min(0, 0, -1);
timevals timevals::sentinel_max(24, 0, 0);

timevals timevals::midnight = timevals();
timevals timevals::noon = timevals(12, 0, 0);

/*
auto timestamp::s_noon = timestamp(12, 0, 0);
auto timestamp::s_midnight = timestamp();

const auto &timestamp::noon = timestamp::s_noon;
const auto &timestamp::midnight = timestamp::s_midnight;

auto timestamp::operator++() noexcept -> timestamp & {
    ++m_sec;

    if (m_sec == max_sec) {
        m_sec = 0;
        
        ++m_min;
    
        if (m_min == max_min) {
            m_min = 0;
            
            ++m_hr;
            
            if (m_hr == max_hr) {
                m_hr = 0;
            }
        }
    }
    
    return *this;
}

auto timestamp::operator++(int) noexcept -> timestamp {
    auto temp(*this);
    ++(*this);
    return temp;
}

auto timestamp::operator--() noexcept -> timestamp & {
    --m_sec;

    if (m_sec == min_hr) {
        m_sec = max_sec - 1;
        
        --m_min;
    
        if (m_min == min_min) {
            m_min = max_min - 1;
            
            --m_hr;
            
            if (m_hr == min_sec) {
                m_hr = max_hr - 1;
            }
        }
    }
    
    return *this;
}

auto timestamp::operator--(int) noexcept -> timestamp {
    auto temp(*this);
    --(*this);
    return temp;
}

auto operator<<(std::ostream &os, const timestamp &ts) noexcept -> std::ostream & {
    char str_hr[3];
    char str_min[3];
    char str_sec[3];
 
    std::sprintf(str_hr, "%s%hd", ts.m_hr < 10 ? "0" : "", ts.m_hr);
    std::sprintf(str_min, "%s%hd", ts.m_min < 10 ? "0" : "", ts.m_min);
    std::sprintf(str_sec, "%s%hd", ts.m_sec < 10 ? "0" : "", ts.m_sec);

    os << str_hr << ":" << str_min << ":" << str_sec;

    return os;
}

auto operator>>(std::istream &is, timestamp &ts) -> std::istream & {
    auto h = 0;
    auto m = 0;
    auto s = 0;
    
    is >> h;
    if (!timestamp::check_hr(h)) {
        throw std::invalid_argument("violated hr invariant: hr >= 0 && hr < 24");
    }
    
    is >> m;
    if (!timestamp::check_min(m)) {
        throw std::invalid_argument("violated min invariant: min >= 0 && min < 60");
    }
    
    is >> s;
    if (!timestamp::check_sec(s)) {
        throw std::invalid_argument("violated sec invariant: sec >= 0 && sec < 60");
    }
    
    ts.m_hr = h;
    ts.m_min = m;
    ts.m_sec = s;
    
    return is;
}
*/
