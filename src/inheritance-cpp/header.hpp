/*!
    \file       header.hpp
    \brief      Header file

    \author
    \date
 */

#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <exception>

///
/// A study/refresher on multiple-inheritance.
///

class buffer {
public:
    using value_type = char;
    using pointer = char *;
    using reference = char &;
    using const_reference = const char &;

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
    buffer() = default;
    
    buffer(size_t size) : m_start(new char[size]),
                          m_finish(m_start + size),
                          m_end_of_storage(m_start + size) {
        std::fill_n(m_start, size, '\0');
    }
    
    buffer(const buffer &b) : m_start(new char[b.capacity()]),
                              m_finish(m_start + b.size()),
                              m_end_of_storage(m_start + b.capacity()) {
        std::copy(b.m_start, b.m_finish, m_start);
    }
    
    buffer(buffer &&b) : m_start(std::exchange(b.m_start, nullptr)),
                         m_finish(std::exchange(b.m_finish, nullptr)),
                         m_end_of_storage(std::exchange(b.m_end_of_storage, nullptr)) {
        
    }
    
    virtual ~buffer() {
        delete[] m_start;
        m_start = m_finish = m_end_of_storage = nullptr;
    }

    auto operator=(const buffer &b) -> buffer &;
    auto operator=(buffer &&b) -> buffer &;
    
    auto size() const -> size_t { return m_finish - m_start; }
    auto capacity() const -> size_t { return m_end_of_storage - m_start; }
    
    friend auto operator<<(std::ostream &os, const buffer &b) -> std::ostream &;
   
protected:
    char *m_start{};
    char *m_finish{};
    char *m_end_of_storage{};
};

class readbuffer : virtual public buffer {
public:
    using const_iterator = const pointer;

    readbuffer() { }
    readbuffer(size_t size) : buffer(size) { }
    readbuffer(const readbuffer &rb) : buffer(rb) { }
    readbuffer(readbuffer &rb) : buffer(std::move(rb)) { }
    
    auto begin() const -> const_iterator { return m_start; }
    auto end() const -> const_iterator { return m_finish; }
   
    auto at(size_t n) const -> const_reference {
        if (n >= size()) {
            throw std::out_of_range("[readbuffer::at(size_t)]: out_of_range");
        }
        
        return *(begin() + n);
    }
};

class writebuffer : virtual public buffer {
public:
    using iterator = pointer;

    writebuffer() { }
    writebuffer(size_t size) : buffer(size) { }
    writebuffer(const writebuffer &wb) : buffer(wb) { }
    writebuffer(writebuffer &wb) : buffer(std::move(wb)) { }

    auto begin() -> iterator { return m_start; }
    auto end() -> iterator { return m_finish; }

    auto set_at(size_t n, value_type val) {
        if (n > size()) {
            throw std::out_of_range("[readbuffer::set_at(size_t, value_type)]: out_of_range");
        }
        
        if (n >= size()) {
            m_finish = begin() + n;
        }
        
        *(begin() + n) = val;
    }
};

class readwritebuffer : public readbuffer, public writebuffer {
public:
    readwritebuffer(size_t size) : buffer(size) { }
    readwritebuffer(const readbuffer &rb) : buffer(rb) { }
    readwritebuffer(readbuffer &rb) : buffer(std::move(rb)) { }

    auto operator[](size_t n) -> reference {
        return *(writebuffer::begin() + n);
    }

    auto operator[](size_t n) const -> const_reference {
        return *(readbuffer::begin() + n);
    }
};


#endif /* HEADER_HPP */

