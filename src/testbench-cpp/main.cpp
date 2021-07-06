/*!
    \file       main.cpp
    \brief      Client source file

    \author
    \date
 */

// Compiled with: g++ -Wall -std=c++14 -pthread
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <algorithm>

namespace gem {
    
template <typename T>
struct snode {
    T m_data;
    snode *m_next;
    
    snode(const T &data) : m_data(data) {}
    
    snode() = default;
    snode(const snode &sn) = default;
    snode(snode &&sn) = default;
    ~snode() {}
    
    static void hook_after(snode *x, snode *y) {
        y->m_next = x->m_next;
        x->m_next = y;
    }
    
    static void unhook_after(snode *y) {
        y->m_next = y->m_next->m_next;   
    }
};
    
template <typename T>
struct snode_iterator {
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    
    snode_iterator(snode<T> *curr) : m_curr(curr) {}
    
    snode_iterator() = default;
    snode_iterator(const snode_iterator &it) = default;
    snode_iterator(snode_iterator &&it) = default;
    ~snode_iterator() {}
    
    reference &operator*() { return m_curr->m_data; }
    pointer *operator->() { return &(m_curr->m_data); }
                       
    snode_iterator &operator++() {
        m_curr = m_curr->m_next;
        return *this;
    }
    
    snode_iterator operator++(int) {
        auto temp(*this);
        m_curr = m_curr->m_next;
        return temp;
    }
    
    snode_iterator &operator=(const snode_iterator &it) {
        m_curr = it.m_curr;
        return *this;
    }
    
    friend bool operator==(const snode_iterator &lhs, const snode_iterator &rhs) {
        return lhs.m_curr == rhs.m_curr;   
    }
    
    friend bool operator!=(const snode_iterator &lhs, const snode_iterator &rhs) {
         return !(lhs == rhs);   
    }
    
    snode<T> *m_curr;
};

  
template <typename T>
struct snode_const_iterator {
    using value_type = T;
    using reference = const T &;
    using pointer = const T *;
    
    snode_const_iterator(const snode<T> *curr) : m_curr(curr) {}
    snode_const_iterator(const snode_iterator<T> &it) : m_curr(it.m_curr) {}
    
    snode_const_iterator() = default;
    snode_const_iterator(const snode_const_iterator &it) = default;
    snode_const_iterator(snode_const_iterator &&it) = default;
    ~snode_const_iterator() {}
    
    reference operator*() const { return m_curr->m_data; }
    pointer operator->() const { return &(m_curr->m_data); }
                       
    snode_const_iterator &operator++() {
        m_curr = m_curr->m_next;
        return *this;
    }
    
    snode_const_iterator operator++(int) {
        auto temp(*this);
        m_curr = m_curr->m_next;
        return temp;
    }
    
    friend bool operator==(const snode_const_iterator &lhs, const snode_const_iterator &rhs) {
        return lhs.m_curr == rhs.m_curr;   
    }
    
    friend bool operator!=(const snode_const_iterator &lhs, const snode_const_iterator &rhs) {
         return !(lhs == rhs);   
    }
    
    const snode<T> *m_curr;
};
    
template <typename T>
class slist {
private:
    snode<T> *m_insert_after(snode<T> *pos, const T &val) {
        auto new_node = new snode<T>(val);
        snode<T>::hook_after(pos, new_node);
        return pos->m_next;
    }
    
    snode<T> *m_erase_after(snode<T> *pos) {
        auto old_node = pos->m_next;
        snode<T>::unhook_after(pos);
        delete old_node;
        return pos->m_next;
    }
    
    snode<T> m_node;
public:
    using iterator = snode_iterator<T>;
    using const_iterator = snode_const_iterator<T>;
    
    slist(std::initializer_list<T> l) {
        auto it = before_begin();
        for (const auto &val : l) {
            it = insert_after(it, val);
        }
    }
    
    slist() = default;
    
    slist(const slist &sl) {
        auto it = before_begin();
        for (const auto &val : sl) {
            it = insert_after(it, val);
        }
    }
    
    slist(slist &&sl) = default;
    
    ~slist() { }
    
    iterator before_begin() {
         return iterator(&m_node);   
    }
    
    iterator begin() {
        return iterator(m_node.m_next);   
    }
    
    iterator end() {
        return iterator(nullptr);
    }
    
    const_iterator before_begin() const {
         return const_iterator(&m_node);   
    }
    
    const_iterator begin() const {
         return const_iterator(m_node.m_next);   
    }
    
    const_iterator end() const {
         return const_iterator(nullptr);   
    }
    
    iterator insert_after(const_iterator pos, const T &val) {
        return iterator(m_insert_after(const_cast<snode<T> *>(pos.m_curr), val));
    }
    
    iterator erase_after(const_iterator pos) {
        return iterator(m_erase_after(const_cast<snode<T> *>(pos.m_curr)));
    }
    
    void push_front(const T &val) {
        insert_after(before_begin(), val);   
    }
    
    void pop_front() {
        erase_after(before_begin());
    }
    
    friend std::ostream &operator<<(std::ostream &os, const slist &l) {
        auto it = std::ostream_iterator<T>(os, " ");
        os << "{ ";
        std::copy(l.begin(), l.end(), it);
        os << "}\n";
        return os;
    }
};
    
   
}

int main() {
    auto sl = gem::slist<int> { 10, 20, 30, 40, 50, 60, 70 };
    std::cout << sl << std::endl;
    
    
    
    return 0;
}


