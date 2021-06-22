#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include <initializer_list>
#include <cmath>

namespace tmpl {

template <typename FloatingPointType>
FloatingPointType euclidean_distance(std::initializer_list<FloatingPointType> l);

}

template <typename FloatingPointType>
FloatingPointType tmpl::euclidean_distance(std::initializer_list<FloatingPointType> l) {
    auto sum = 0.0;
    const auto dim = l.end() - l.begin();

    for (auto element : l) {
        sum += std::pow(element, dim);
    }

    return std::sqrt(sum);
}

#endif /* TEMPLATE_HPP */
