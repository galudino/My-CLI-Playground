/*!
    \file       timestamp.hpp
    \brief      Header file to model a 24-hr timestamp with countdown/countup features

    \author     Gemuele Aludino
    \date       02 Jul 2021
 */

#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <stdexcept>
#include <string>

void output_elipsis(std::ostream &os, const std::string &description = "",
                    char elipsis = '.', int char_count = 3, int iterations = 1);

class timestamp {
public:
    timestamp(int16_t hr = 0, int16_t min = 0, int16_t sec = 0)
    : m_hr(hr), m_min(min), m_sec(sec) {
        if (!check_hr(hr)) {
            throw std::invalid_argument("violated hr invariant: hr >= 0 && hr < 24");
        }
        
        if (!check_min(min)) {
            throw std::invalid_argument("violated min invariant: min >= 0 && min < 60");
        }
        
        if (!check_sec(sec)) {
            throw std::invalid_argument("violated sec invariant: sec >= 0 && sec < 60");
        }
    }
    
    timestamp(const timestamp &ts) = default;
    timestamp(timestamp &&ts) = default;

    int16_t hr() const { return m_hr; }
    int16_t min() const { return m_min; }
    int16_t sec() const { return m_sec; }
    
    void set_hr(int16_t hour) {
        if (!check_hr(hour)) {
            throw std::invalid_argument("violated hr invariant: hr >= 0 && hr < 24");
        }
        
        m_hr = hour;
    }
    
    void set_min(int16_t minute) {
        if (!check_min(minute)) {
            throw std::invalid_argument("violated min invariant: min >= 0 && min < 60");
        }
        
        m_min = minute;
    }
    
    void set_sec(int16_t second) {
        if (!check_sec(second)) {
            throw std::invalid_argument("violated sec invariant: sec >= 0 && sec < 60");
        }
        
        m_sec = second;
    }
    
    bool same_hr(const timestamp &rhs) const { return m_hr == rhs.m_hr; }
    bool same_min(const timestamp &rhs) const { return m_min == rhs.m_min; }
    bool same_sec(const timestamp &rhs) const { return m_sec == rhs.m_sec; }
    
    std::string to_string() const {
        using std::string_literals::operator""s;

        auto str = std::string(timestamp_char_count, ' ');

        str = (m_hr < 10 ? "0"s : ""s) + std::to_string(m_hr) + ":"s
            + (m_min < 10 ? "0"s : ""s) + std::to_string(m_min) + ":"s
            + (m_sec < 10 ? "0"s : ""s) + std::to_string(m_sec);
        
        return str;
    }
    
    timestamp &count_down_to(const timestamp &end, std::ostream &os);
    timestamp &count_up_to(const timestamp &end, std::ostream &os);
    
    timestamp &operator++();
    timestamp operator++(int);
    timestamp &operator--();
    timestamp operator--(int);
    
    timestamp &operator=(const timestamp &ts) = default;
    timestamp &operator=(timestamp &&ts) = default;
    
    friend bool operator==(const timestamp &lhs, const timestamp &rhs) {
        return lhs.same_hr(rhs) && lhs.same_min(rhs) && lhs.same_sec(rhs);
    }
    
    friend bool operator<(const timestamp &lhs, const timestamp &rhs) {
        if (lhs.hr() < rhs.hr()) { return true; }   // 03:00:00 vs 04:00:00
        if (lhs.min() < rhs.min()) { return true; } // 03:00:00 vs 03:01:00
        if (lhs.sec() < rhs.sec()) { return true; } // 03:00:00 vs 03:00:01
        return false;                               // 03:00:01 vs 03:00:00
    }
    
    friend bool operator<=(const timestamp &lhs, const timestamp &rhs) {
        return lhs < rhs || lhs == rhs;
    }
    
    friend bool operator>(const timestamp &lhs, const timestamp &rhs) {
        return !(lhs < rhs);
    }
    
    friend bool operator>=(const timestamp &lhs, const timestamp &rhs) {
        return lhs > rhs || lhs == rhs;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const timestamp &ts);
    friend std::istream &operator>>(std::istream &is, timestamp &ts);
    
    static const timestamp &noon;
    static const timestamp &midnight;

private:
    static bool check_hr(uint16_t hr) { return hr >= 0 && hr < max_hr; }
    static bool check_min(uint16_t min) { return min >= 0 && min < max_min; }
    static bool check_sec(uint16_t sec) { return sec >= 0 && sec < max_sec; }
    
    static constexpr auto max_hr = 24;
    static constexpr auto max_min = 60;
    static constexpr auto max_sec = 60;
    
    static constexpr auto min_hr = -1;
    static constexpr auto min_min = -1;
    static constexpr auto min_sec = -1;
    
    static constexpr auto timestamp_char_count = 8;
    
    static timestamp s_noon;
    static timestamp s_midnight;
    
    int16_t m_hr;
    int16_t m_min;
    int16_t m_sec;
};

#endif /* TIMESTAMP_HPP */
