/*!
    \file       matrix_impl.hpp
    \brief      Template implementation details for matrix.hpp
                (spiralify, and operator<< functions for square_matrix)

    \details    This is an internal header file included by matrix.hpp.
                Do not include this header anywhere else!

    \author     Gem Aludino
    \date       31 Mar 2021
 */


/*!
    \brief  Takes a gem::square_matrix<T, N> and populates it
            such that it forms a "spiral".

    \tparam     T   datatype
    \tparam     N   Dimension of square matrix. (N * N matrix)
    
    \param[in][out] sm  reference to std::array<std::array<T, N>, N>

    \return     true if N > 0 && (N ^ 1 != N + 1)
                Function returns true upon successful completion.
 */
template <typename T, size_t N>
bool gem::spiralify(gem::square_matrix<T, N> &sm) {
    if (N <= 0) { return false; }

    constexpr auto last_index = N - 1;

    auto col_bound_east = last_index;  // last index when moving east
    auto row_bound_south = last_index; // last index when moving south
    auto col_bound_west = 0;           // last index when moving west
    auto row_bound_north = 0;          // last index when moving north

    auto row_pos = 0;
    auto col_pos = 0;

    auto K = N * N;

    // The while loop below will populate all but the center element.

    // col_bound_east == row_bound_north means the bounds have met
    // in the center of the matrix. 
    // sm[row_bound_north][col_bound_east] is the center of the matrix.

    while (col_bound_east != row_bound_north) {
        // Move eastbound.
        while (col_pos < col_bound_east) {
            sm[row_pos][col_pos++] = K--;
        }

        // Move southbound.
        while (row_pos < row_bound_south) {
            sm[row_pos++][col_pos] = K--;
        }

        // Move westbound.
        while (col_pos > col_bound_west) {
            sm[row_pos][col_pos--] = K--;
        }

        // Move northbound.
        while (row_pos > row_bound_north) {
            sm[row_pos--][col_pos] = K--;
        }

        // Prepare the east and south boundaries for the next iteration.
        --col_bound_east;       // Move the east boundary westward.
        --row_bound_south;      // Move the south boundary northward.

        // Prepare the west and north boundaries for the next iteration.
        ++col_bound_west;       // Move the west boundary eastward.
        ++row_bound_north;      // Move the north boundary southward.

        // Make sure the next iteration begins on the correct row/column.
        // Use the delta of last_index and row_bound_down to determine the row_pos start position.
        // Use the delta of last_index and col_bound_right to determine the col_pos start position.
        row_pos = last_index - row_bound_south;
        col_pos = last_index - col_bound_east;
    }
    
    // row_pos, col_pos, 
    // row_bound_north, row_bound_south, 
    // col_bound_west, and col_bound_east
    // are all the same value.
    // sm[row_pos][col_pos] represents the center of the matrix.
    
    sm[row_pos][col_pos] = K;       // Assigning K = 1 to the center.

    return true;
}

// Output a gem::square_matrix<T, N> to a stream
template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const gem::square_matrix<T, N> &sm) {
    for (const auto &r : sm) {
        for (const auto &elem : r) {
            os << elem << " ";
        }

        os << '\n';
    }

    return os;
}

