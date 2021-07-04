/*!
    \file       source.cpp
    \brief      Source file

    \author
    \date
 */

#include "header.hpp"
#include <iomanip>
#include <queue>

/*!
    \brief  Constructor with initializer list
    \param[in]  list    of format { { 0, 1, 2, ... },  { 1, 0, 2, ... },  { 2, 0, 1, ... }, ... }
    In each sub-list, the first element is the vertex identifier.
    Subsequent elements in a sub-list are the first element's adjacent vertices.
 */
graph::graph(std::initializer_list<std::initializer_list<int>> list) {
    // for all integer lists in list
    for (auto intlist : list) {
        // Create the adjacency_list.
        // Once it is fully populated, we will add it to the graph.
        adjacency_list adjlist;
        
        // We want to append elements to our adjacency_list
        // (a forward_list<int>) from front to back.
        // forward_list only has push_front, but we can still append
        // to the back by maintaining an iterator to the back.
        auto adjlist_pos = adjlist.before_begin();
        
        // The first element in intlist is the vertex id.
        // Subsequent elements in intlist are the adjacent vertices.
        // Since the key index in our final adjacency list already
        // identifies the origin vertex in an edge, we don't need to
        // keep (*intlist.begin()).
        auto intlist_pos = intlist.begin();
        ++intlist_pos; // We just need the integers after intlist.begin().
        
        while (intlist_pos < intlist.end()) {
            adjlist_pos = adjlist.insert_after(adjlist_pos, *(intlist_pos++));
        }
        
        // Now that the adjacency list is fully populated,
        // we can add it to our vector of adjacency lists.
        m_graph.push_back(adjlist);
    }
}

/*!
    \brief  Add a vertex to *this
    \post   An empty adjacency_list (std::forward_list<int>) is appended to m_graph.
    \return size() - 1, or the index of the newly inserted vertex
 */
int graph::add_vertex() {
    m_graph.push_back(adjacency_list());
    return size() - 1;
}

/*!
    \brief  Add an edge to *this
    \param[in]  origin_vertex_id starting vertex for an edge
    \param[in]  destination_vertex_id ending vertex for an edge
    \post   If origin_vertex and destination_vertex exist, and they do not make an edge,
            an edge to origin_vertex and destination_vertex will be created
    \return true, if the edge was successfully added, false otherwise
 */
bool graph::add_edge(int origin_vertex_id, int destination_vertex_id) {
    // if origin_vertex >= size() return
    // if destination_vertex >= size() return
    
    // var adjlist_origin = m_graph[origin_vertex]
    // var adjlist_destination = m_graph[destination_vertex]
    
    // only add the edge if it doesnt already exist.
    // adjlist_origin must not have destination_vertex
    // and adjlist_destination must not have origin_vertex
    // if adjlist_origin.find(destination_vertex) == false
    //  && adjlist_destination.find(origin_vertex) == false
    // adjlist_origin.add(destination_vertex)
    // destination_vertex.add(origin_vertex)
    return false;
}

/*!
    \brief  Remove an edge from *this
    \param[in]  origin_vertex_id starting vertex for an edge
    \param[in]  destination_vertex_id ending vertex for an edge
    \post   destination_vertex is removed from m_graph[origin_vertex]
            origin_vertex is removed from m_graph[destination_vertex]
    \return true, if the edge was successfully removed, false otherwise
 */
bool graph::remove_edge(int origin_vertex_id, int destination_vertex_id) {
    // To remove an edge (i, k)
    // If i >= g.size(), vertex i does not exist. return.
    // If k >= g.size(), vertex k does not exist. return.
    // Else:
    //      var adjlist_origin = g.m_graph[i]
    //      adjlist_origin.remove(vertex: k)
    //      var adjlist_dest = g.m_graph[k]
    //      adjlist_dest.remove(vertex: i)
    return false;
}

/*!
    \brief  Remove a vertex from *this
    \post   The adjacency_list, m_graph[vertex_id],
            and all instances of vertex_id from other adjacency_lists in m_graph
            will be removed.
    \return true, if the vertex was successfully removed, false otherwise
 */
bool graph::remove_vertex(int vertex_id) {
    // if vertex_id >= size(), return false
    // var adjlist = m_graph[vertex_id]
    // for all vertex in adjlist
    //      m_graph[vertex].remove(vertex_id)
    // m_graph.remove(vertex_id)
    return false;
}

/*!
    \brief  Retrieve the std::forward_list<int> of adjacent vertices to the vertex at `vertex_id`
    \post   The adjacency list at m_graph[vertex_id] is returned
    \return Immutable reference to `vertex_id`'s adjacency_list
 */
const graph::adjacency_list &graph::operator[](int vertex_id) const {
    return m_graph[vertex_id];
}

size_t graph::size() const {
    return m_graph.size();
}

/*!
    \brief  Determines whether graph is empty
    \post   Returns true if graph is empty, false otherwise
    \return true if size() == 0, false otherwise
 */
bool graph::empty() const {
    return m_graph.empty();
}

/*!
    \brief  Prints graph
    \post   Graph is printed to stdout
 */
void graph::print() const {
    std::cout << *this << std::endl;
}

/*!
    \brief  Performs depth-first traversall on the entire graph
    \post   Vertices of the graph are printed to stdout using the DFS algorithm
 */
void graph::depth_first_traversal() {
    auto visited = std::vector<bool>(size());
    
    std::cout << "DFS: {";
    // for each vertex not visited, do a dfs
    for (auto vertex = 0; vertex < size(); vertex++) {
        if (visited[vertex] == false) {
            m_dft(vertex, visited);
        }
    }
    std::cout << "}\n";
}

/*!
    \brief  Performs depth-first traversal of the graph at a node specified by the parameter `vertex`.
    \param[in]  vertex_id  starting vertex for the DFS algorithm
    \post   Starting at `vertex`, the vertices are printed using the DFS algorithm
    \return true, if DFS was successful, false otherwise
 */
bool graph::depth_first_traversal(int vertex_id) {
    if (vertex_id >= size()) { return false; }
    
    auto visited = std::vector<bool>(size());
    std::cout << "DFS at " << vertex_id << ": {";
    m_dft(vertex_id, visited);
    std::cout << "}\n";
    
    return true;
}

/*!
    \brief  Performs breadth-first traversal of the entire graph.
    \post   Vertices of the graph are printed to stdout using the BFS algorithm
 */
void graph::breadth_first_traversal() {
    auto queue = std::queue<int>();
    
    auto visited = std::vector<bool>(size());
    
    auto graph_it = adjacency_list::iterator();
    
    std::cout << "BFS: {";
    for (auto vertex = 0; vertex < size(); vertex++) {
        if (visited[vertex] == false) {
            queue.push(vertex);
            
            // visit the vertex
            std::cout << ' ' << vertex << ' ';
            visited[vertex] = true;
            
            while (!queue.empty()) {
                auto u = queue.front();
                queue.pop();
                
                for (graph_it = m_graph[u].begin();
                     graph_it != m_graph[u].end(); ++graph_it) {
                    int w = *graph_it;
                    if (visited[w] == false) {
                        queue.push(w);
                        
                        // visit the vertex
                        std::cout << ' ' << w << ' ';
                        visited[w] = true;
                    }
                }
            }
        }
    }
    std::cout << "}\n";
}

/*!
    \brief  Clears the graph
    \post   Memory occupied by each vertex is deallocated
 */
void graph::clear() {
    m_graph.clear();
}

/*!
    \brief  Outputs graph `g` via `os`, a stream-insertion operator
    \param[out] os  output stream for graph `g`
    \param[in]  g    graph to output for stream
 
    \post   A string representation of `g` is output to `os`
    \return Contents of `g` written to `os`
 */
std::ostream &operator<<(std::ostream &os, const graph &g) {
    os << "graph " << &g << " {\n";
    auto vertex = 0;
    for (const auto &adjlist : g.m_graph) {
        os << std::setw(4) << '(' << vertex++ << "): ";
        
        os << "{ ";
        auto it = adjlist.begin();
        while (it != adjlist.end()) {
            os << *(it++) << ' ';
        }
        os << "}\n";
    }
    os << "}\n";
    return os;
}

void graph::m_dft(int v, std::vector<bool> &visited) {
    visited[v] = true;
    
    // visit the vertex
    std::cout << " " << v << " ";
    
    auto graph_it = m_graph[v].begin();
    while (graph_it != m_graph[v].end()) {
        int w = *(graph_it++);
        
        if (!visited[w]) {
            m_dft(w, visited);
        }
    }
}
