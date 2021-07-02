#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <exception>

struct timevals;

struct timestamp_iterator;
struct timestamp_reverse_iterator;

struct timestamp_const_iterator;
struct timestamp_const_reverse_iterator;

class timestamp;

struct timevals {
public:
    int16_t m_hr;
    int16_t m_min;
    int16_t m_sec;
    
    timevals(int16_t hr = 0, int16_t min = 0, int16_t sec = 0) : m_hr(hr), m_min(min), m_sec(sec) {}
    
    static timevals midnight;
    static timevals noon;
    
    static timevals sentinel_min; // for timestamp::rend()
    static timevals sentinel_max; // for timestamp::end()
    
    static constexpr auto max_hr = 24;
    static constexpr auto max_min = 60;
    static constexpr auto max_sec = 60;
    
    static constexpr auto min_hr = -1;
    static constexpr auto min_min = -1;
    static constexpr auto min_sec = -1;

    static auto check_hr(uint16_t hr) noexcept -> bool { return hr >= 0 && hr < max_hr; }
    static auto check_min(uint16_t min) noexcept -> bool { return min >= 0 && min < max_min; }
    static auto check_sec(uint16_t sec) noexcept -> bool { return sec >= 0 && sec < max_sec; }
};

struct timestamp_iterator {
    timevals &m_vals;
    
    timestamp_iterator(timevals &tv) : m_vals(tv) {}
    
    timevals &operator*() { return m_vals; }
    timevals *operator->() { return &m_vals; }
    
    timestamp_iterator &operator++() {
        return *this;
    }
    
    timestamp_iterator operator++(int) {
        auto temp(*this);
        return temp;
    }
    
    timestamp_iterator &operator--() {
        return *this;
    }
    
    timestamp_iterator operator--(int) {
        auto temp(*this);
        return temp;
    }
};

struct timestamp_reverse_iterator {
    timevals &m_vals;
    
    timestamp_reverse_iterator(timevals &tv) : m_vals(tv) {}
    
    timevals &operator*() { return m_vals; }
    timevals *operator->() { return &m_vals; }
    
    timestamp_reverse_iterator &operator++() {
        return *this;
    }
    
    timestamp_reverse_iterator operator++(int) {
        auto temp(*this);
        return temp;
    }
    
    timestamp_reverse_iterator &operator--() {
        return *this;
    }
    
    timestamp_reverse_iterator operator--(int) {
        auto temp(*this);
        return temp;
    }
};

struct timestamp_const_iterator {
    const timevals &m_vals;
    
    timestamp_const_iterator(const timevals &tv) : m_vals(tv) {}
    
    const timevals &operator*() { return m_vals; }
    const timevals *operator->() { return &m_vals; }
    
    timestamp_const_iterator &operator++() {
        return *this;
    }
    
    timestamp_const_iterator operator++(int) {
        auto temp(*this);
        return temp;
    }
    
    timestamp_const_iterator &operator--() {
        return *this;
    }
    
    timestamp_const_iterator operator--(int) {
        auto temp(*this);
        return temp;
    }
};

struct timestamp_const_reverse_iterator {
    const timevals &m_vals;
    
    timestamp_const_reverse_iterator(const timevals &tv) : m_vals(tv) {}
    
    const timevals &operator*() { return m_vals; }
    const timevals *operator->() { return &m_vals; }
    
    timestamp_const_reverse_iterator &operator++() {
        return *this;
    }
    
    timestamp_const_reverse_iterator operator++(int) {
        auto temp(*this);
        return temp;
    }
    
    timestamp_const_reverse_iterator &operator--() {
        return *this;
    }
    
    timestamp_const_reverse_iterator operator--(int) {
        auto temp(*this);
        return temp;
    }
};

class timestamp {
public:
    using iterator = timestamp_iterator;
    using const_iterator = timestamp_const_iterator;
    using reverse_iterator = timestamp_reverse_iterator;
    using const_reverse_iterator = timestamp_const_reverse_iterator;
    
    timestamp(int16_t hr = 0, int16_t min = 0, int16_t sec = 0) : m_vals{hr, min, sec} {}
    
    int16_t hr() const { return m_vals.m_hr; }
    int16_t min() const { return m_vals.m_min; }
    int16_t sec() const { return m_vals.m_sec; }
    
    void set_hr(int16_t hr) {
        
    }
    
    void set_min(int16_t min) {
        
    }
    
    void set_sec(int16_t sec) {
        
    }
    
    bool same_hr(const timestamp &ts) const;
    bool same_min(const timestamp &ts) const;
    bool same_sec(const timestamp &ts) const;
    
    iterator begin() { return iterator(m_vals); }
    iterator end() { return iterator(timevals::sentinel_max); }
    
    const_iterator begin() const {
        return const_iterator(m_vals);
    }
    
    const_iterator end() const {
        return const_iterator(timevals::sentinel_max);
    }
    
    reverse_iterator rbegin() {
        return reverse_iterator(m_vals);
    }
    
    reverse_iterator rend() {
        return reverse_iterator(timevals::sentinel_min);
    }
    
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(m_vals);
    }
    
    const_reverse_iterator rend() const {
        return const_reverse_iterator(timevals::sentinel_min);
    }
    
    friend bool operator==(const timestamp &lhs, const timestamp &rhs);
    
    friend bool operator<(const timestamp &lhs, const timestamp &rhs);
    
    friend std::ostream &operator<<(std::ostream &os, const timestamp &ts);
    
    friend std::istream &operator>>(std::istream &is, timestamp &ts);
    
private:
    timevals m_vals;
};


/// Use this code and fit it with the refactored classes.
/// The overloaded ++/-- operators should go with the iterators.
/// This will also class timestamp to have a begin(), end(), rbegin(), rend(), and const
/// versions of each. return value of begin() depends on the state of the timevals
/// field within timestamp.
///
/// The main idea is that timevals holds the time data itself,
/// the iterators mutate its state,
/// and the timestamp provides access to its timevals field through its public API.
/*
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
    
    timestamp(const timestamp &ts) noexcept = default;
    timestamp(timestamp &&ts) noexcept = default;

    auto hr() const noexcept -> int16_t { return m_hr; }
    auto min() const noexcept -> int16_t { return m_min; }
    auto sec() const noexcept -> int16_t { return m_sec; }
    
    auto set_hr(int16_t hour) {
        if (!check_hr(hour)) {
            throw std::invalid_argument("violated hr invariant: hr >= 0 && hr < 24");
        }
        
        m_hr = hour;
    }
    
    auto set_min(int16_t minute) {
        if (!check_min(minute)) {
            throw std::invalid_argument("violated min invariant: min >= 0 && min < 60");
        }
        
        m_min = minute;
    }
    
    auto set_sec(int16_t second) {
        if (!check_sec(second)) {
            throw std::invalid_argument("violated sec invariant: sec >= 0 && sec < 60");
        }
        
        m_sec = second;
    }
    
    auto same_hr(const timestamp &rhs) const noexcept -> bool { return m_hr == rhs.m_hr; }
    auto same_min(const timestamp &rhs) const noexcept -> bool { return m_min == rhs.m_min; }
    auto same_sec(const timestamp &rhs) const noexcept -> bool { return m_sec == rhs.m_sec; }
    
    auto operator++() noexcept -> timestamp &;
    auto operator++(int) noexcept -> timestamp;
    auto operator--() noexcept -> timestamp &;
    auto operator--(int) noexcept -> timestamp;
    
    auto operator=(const timestamp &ts) noexcept -> timestamp & = default;
    auto operator=(timestamp &&ts) noexcept -> timestamp & = default;
    
    friend auto operator==(const timestamp &lhs, const timestamp &rhs) noexcept -> bool {
        return lhs.same_hr(rhs) && lhs.same_min(rhs) && lhs.same_sec(rhs);
    }
    
    friend auto operator<(const timestamp &lhs, const timestamp &rhs) noexcept -> bool {
        if (lhs.hr() < rhs.hr()) { return true; }   // 03:00:00 vs 04:00:00
        if (lhs.min() < rhs.min()) { return true; } // 03:00:00 vs 03:01:00
        if (lhs.sec() < rhs.sec()) { return true; } // 03:00:00 vs 03:00:01
        return false;                               // 03:00:01 vs 03:00:00
    }
    
    friend auto operator<<(std::ostream &os, const timestamp &ts) noexcept -> std::ostream &;
    friend auto operator>>(std::istream &is, timestamp &ts) -> std::istream &;
    
    static const timestamp &noon;
    static const timestamp &midnight;
    
    static constexpr auto max_hr = 24;
    static constexpr auto max_min = 60;
    static constexpr auto max_sec = 60;
    
    static constexpr auto min_hr = -1;
    static constexpr auto min_min = -1;
    static constexpr auto min_sec = -1;

private:
    static auto check_hr(uint16_t hr) noexcept -> bool { return hr >= 0 && hr < max_hr; }
    static auto check_min(uint16_t min) noexcept -> bool { return min >= 0 && min < max_min; }
    static auto check_sec(uint16_t sec) noexcept -> bool { return sec >= 0 && sec < max_sec; }
    
    int16_t m_hr;
    int16_t m_min;
    int16_t m_sec;
    
    static timestamp s_noon;
    static timestamp s_midnight;
};
*/

#endif /* HEADER_HPP */

