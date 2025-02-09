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
#include <forward_list>
#include <memory>
#include <algorithm>
#include <functional>
#include <exception>

class graph {
public:
    using adjacency_list = std::forward_list<int>;
    
    graph(std::initializer_list<std::initializer_list<int>> list);
    
    graph() = default;
    graph(const graph &g) = default;
    graph(graph &&g) = default;
    
    virtual ~graph() {}

    auto operator=(const graph &g) -> graph & = default;
    auto operator=(graph &&g) -> graph & = default;
    
    auto add_vertex() -> int;
    auto remove_vertex(int vertex_id) -> bool;
    
    auto add_edge(int origin_vertex_id, int destination_vertex_id) -> bool;
    auto remove_edge(int origin_vertex_id, int destination_vertex_id) -> bool;
    
    auto operator[](int vertex_id) const -> const adjacency_list &;
    
    size_t size() const;
    bool empty() const;
    void print() const;
    
    void depth_first_traversal();
    bool depth_first_traversal(int vertex_id);
    void breadth_first_traversal();
    
    void clear();
    
    friend std::ostream &operator<<(std::ostream &os, const graph &g);
protected:
    std::vector<adjacency_list> m_graph;
private:
    void m_dft(int v, std::vector<bool> &visited);
};

class weighted_graph : public graph {
public:
    weighted_graph() = default;
    
    weighted_graph(const weighted_graph &wg) = default;
    weighted_graph(weighted_graph &&wg) = default;
    
    weighted_graph &operator=(const weighted_graph &wg) = default;
    weighted_graph &operator=(weighted_graph &&wg) = default;
    
    void create_weighted_graph();
    
    void shortest_path(int vertex_id);
    void print_shortest_distance(int vertex_id);
protected:
    std::vector<std::vector<double>> m_weights;
    std::vector<double> m_smallest_weight;
};

#endif /* HEADER_HPP */

