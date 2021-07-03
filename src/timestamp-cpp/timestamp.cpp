/*!
    \file       timestamp.cpp
    \brief      Source file to model a 24-hr timestamp with countdown/countup features

    \author     Gemuele Aludino
    \date       02 Jul 2021
 */


#include "timestamp.hpp"
#include <iostream>
#include <thread>

/*!
    \brief  Prints dots (elipsis) i.e. for a "Please wait..." prompt
 
    \param[out] os                          output stream for elipsis
    \param[in]  description      appears before elipsis, i.e. "Please wait..."
    \param[in]  elipsis_count  denotes how many elipsis print before cursor backspaces
    \param[in]  iterations        denotes how many runs of elipsis printouts there will be
 */
void output_elipsis(std::ostream &os,
                    const std::string &description,
                    char elipsis,
                    int char_count,
                    int iterations) {
    using std::chrono_literals::operator""ms;
    
    int count = 0;
    const auto move_back_chars = std::string(char_count, '\b');

    os << description;
    while (iterations > 0) {
        os << '.';

        ++count;
        os.flush();
        std::this_thread::sleep_for(1000ms);
        
        if (count == char_count) {
            os << move_back_chars;
            count = 0;
            
            --iterations;
        }
    }

    os << move_back_chars << std::string(description.size() + char_count, ' ');
}

auto timestamp::s_noon = timestamp(12, 0, 0);
auto timestamp::s_midnight = timestamp();

const auto &timestamp::noon = timestamp::s_noon;
const auto &timestamp::midnight = timestamp::s_midnight;

timestamp &timestamp::count_down_to(const timestamp &end, std::ostream &os) {
    using std::chrono_literals::operator""s;
    
    // use this to backspace the cursor timestamp_char_count times
    const auto move_back_chars = std::string(timestamp_char_count, '\b');
    
    while (*this != end) {
        // output the current timestamp
        os << (*this);
        
        // flush the output stream
        os.flush();
    
        // backspace move_back_chars characters
        os << move_back_chars;
        
        // sleep this thread for 1 second
        std::this_thread::sleep_for(1s);
        
        // decrement the current timestamp
        --(*this);
    }
    
    // output the end timestamp
    os << (*this);
    os.flush();
    os << move_back_chars;
    
    return *this;
}

timestamp &timestamp::count_up_to(const timestamp &end, std::ostream &os) {
    using std::chrono_literals::operator""s;
    
    // use this to backspace the cursor timestamp_char_count times
    const auto move_back_chars = std::string(timestamp_char_count, '\b');
    
    while (*this != end) {
        // output the current timestamp
        os << (*this);
        
        // flush the output stream
        os.flush();
    
        // backspace move_back_chars characters
        os << move_back_chars;
        
        // sleep this thread for 1 second
        std::this_thread::sleep_for(1s);
        
        // increment the current timestamp
        ++(*this);
    }
    
    // output the end timestamp
    os << (*this);
    os.flush();
    os << move_back_chars;
    
    return *this;
}

timestamp &timestamp::operator++() {
    ++m_sec;
 
    if (m_sec == max_sec) {
        m_sec = 0;
        ++m_min;
    }
 
    if (m_min == max_min) {
        m_min = 0;
        ++m_hr;
    }
 
    if (m_hr == max_hr) {
        m_hr = 0;
    }
    
    return *this;
}

timestamp timestamp::operator++(int) {
    auto temp(*this);
    ++(*this);
    return temp;
}

timestamp &timestamp::operator--() {
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

timestamp timestamp::operator--(int) {
    auto temp(*this);
    --(*this);
    return temp;
}

std::ostream &operator<<(std::ostream &os, const timestamp &ts) {
    os << (ts.m_hr < 10 ? "0" : "") << ts.m_hr << ':'
       << (ts.m_min < 10 ? "0" : "") << ts.m_min << ':'
       << (ts.m_sec < 10 ? "0" : "") << ts.m_sec;
    
    return os;
}

std::istream &operator>>(std::istream &is, timestamp &ts) {
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

