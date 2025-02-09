/*!
    \file       source.cpp
    \brief      Source file

    \author
    \date
 */

#include "header.hpp"

#include <array>

class tokenizer {
public:
    constexpr auto BUFFER_SIZE = 8;
    
    tokenizer(const char *filepath, uint8_t delimiter = ',', uint8_t override_char = '"');
    tokenizer(std::ifstream &infile, uint8_t delimiter = ',', uint8_t override_char = '"');
    tokenizer(const std::vector<char> &filebytes, uint8_t delimiter = ',', uint8_t override_char = '"');
    
    std::vector<std::string> next_row(std::size_t csv_col_size);
    
    void parse_cells(std::vector<std::string> &cellstore);
    
    bool buffer_remains() const;
    
    uint8_t curr_char() const;
    
private:
    
    std::array<uint8_t, BUFFER_SIZE> m_readbuf;
    std::array<uint8_t, BUFFER_SIZE>::iterator m_readbuf_pos;
    std::array<uint8_t, BUFFER_SIZE>::iterator m_readbuf_end;
    
    uint8_t m_delimiter;
    uint8_t m_override_char;
    
    std::size_t m_readbuf_count;
    
    bool m_end_of_cell;
    bool m_end_of_row;
    bool m_delimiter_override;
    
    std::string m_tokenstore;
};
