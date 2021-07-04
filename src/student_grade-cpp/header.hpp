/*!
    \file       header.hpp
    \brief      Header file

    \author
    \date
 */

#ifndef HEADER_HPP
#define HEADER_HPP

#include <array>
#include <algorithm>
#include <string>
#include <ostream>
#include <istream>

class student {
public:
    static constexpr auto grades_count = 5;

    using grades_set = std::array<double, grades_count>;

    student() = default;
    student(const student &s) = default;
    student(student &&s) = default;

    student(const std::string &first_name, 
            const std::string &last_name,
            const grades_set &grades)
        : m_first_name(first_name), m_last_name(last_name),
          m_grades(grades) { }

    student(const std::string &filename);

    ~student() { }

    student &operator=(const student &s) = default;
    student &operator=(student &&s) = default;
    
    double average() const;

    friend std::ostream &operator<<(std::ostream &os, const student &s);
    friend std::istream &operator>>(std::istream &is, student &s);
private:
    std::string m_first_name;
    std::string m_last_name;
    
    grades_set m_grades;
};

#endif /* HEADER_HPP */

