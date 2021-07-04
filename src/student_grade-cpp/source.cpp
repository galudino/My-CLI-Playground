/*!
    \file       source.cpp
    \brief      Source file

    \author
    \date
 */

#include "header.hpp"
#include <fstream>
#include <iomanip>

student::student(const std::string &filename) {
    auto input_file = std::ifstream();
    input_file.open(filename);

    input_file >> *this;
    input_file.close();
}

double student::average() const {
    auto sum = 0.0;
    std::for_each(m_grades.begin(), m_grades.end(),
                 [&sum](double score) { sum += score; });
    return sum / student::grades_count;
}

std::ostream &operator<<(std::ostream &os, const student &s) {
    os << "Student name: " << s.m_first_name << ' ' << s.m_last_name << '\n';
    
    os << "Test scores: ";
    std::for_each(s.m_grades.begin(), s.m_grades.end(), 
                  [&os](double score) { 
                    os << std::fixed 
                       << std::showpoint 
                       << std::setprecision(2) << score << ' '; 
                  } 
    );

    os << "\nAverage test score: " << s.average() << '\n';
    return os;
}

std::istream &operator>>(std::istream &is, student &s) {
    is >> s.m_first_name;
    is >> s.m_last_name;
    
    for (auto i = 0; i < student::grades_count; i++) {
        is >> s.m_grades[i];
    }

    return is;
}
