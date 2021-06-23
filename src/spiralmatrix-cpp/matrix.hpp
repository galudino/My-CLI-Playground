/*!
    \file       matrix.hpp
    \brief      Header for square_matrix template

    \details    gem::square_matrix<T, N> is a type alias for
                std::array<std::array<T, N>, N>.

    \author     Gem Aludino
    \date       31 Mar 2021
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include <ostream>

namespace gem {

// type alias for a row within an matrix
template <typename T, size_t N>
using row = std::array<T, N>;

// type alias for an N * N matrix
template <typename T, size_t N>
using square_matrix = std::array<gem::row<T, N>, N>;

template <typename T, size_t N>
bool spiralify(gem::square_matrix<T, N> &sm);

template <typename T>
constexpr bool is_odd(T val) { return (val ^ 1) != (val + 1); }

} // namespace gem

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const gem::square_matrix<T, N> &sm);

#include "matrix_impl.hpp"

#endif /* MATRIX_HPP */
