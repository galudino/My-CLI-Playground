/*!
    \file       graphType.cpp
    \brief      Source file

    \author
    \date
 */

#include "graphType.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <sstream>

void graphType::createGraph() {
    auto infile = std::ifstream();
    auto fileName = std::string();
  
    std::cout << "Enter input file name: ";
    std::cin >> fileName;
    std::cout << std::endl;

    infile.open(fileName);

    if (!infile) {
        std::cout << "Cannot open input file." << std::endl;
        return;
    }

    createGraph(fileName);
}

void graphType::createGraph(const std::string &filename) {
    auto infile = std::ifstream();
    infile.open(filename);
    
    if (!infile) {
        std::cerr << "Cannot open input file." << std::endl;
        return;
    }

    createGraph(infile);
    infile.close();
}


/*!
    \details
    Expected input file format:
    [vertex count]
    [vertex 0] [adjacent vertex 0] [adjacent vertex 2] ... [adjacent vertex n]
    ...

    Example:
    3
    0 1 2
    1 0 1
    2 0 1
 */
void graphType::createGraph(std::ifstream &infile) {
    if (!isEmpty()) {
        clearGraph();
    }
    
    // Store a vector of strings to store the file, line by line
    auto lines = std::vector<std::string>();
    
    // Capture the file, line by line
    auto str = std::string();
    while (std::getline(infile, str)) {
        // Make sure we don't add any empty lines.
        if (str.empty()) { break; }
        lines.push_back(str);
    }
    
    // Use a stringstream to retrieve the total vertex count
    // from the first line in the file.
    auto isstr = std::istringstream(lines[0]);
    auto vertex_count = -1;
    isstr >> vertex_count;
    
    // Create a vector of adjacency lists.
    // We know the total vertex count already,
    // so let's allocate that in advance.
    graph.resize(vertex_count);

    // Iterate from [lines.begin() + 1, lines.end())
    // to capture the adjacent vertices for the current vertex.
    for (auto lines_it = lines.begin() + 1; lines_it < lines.end(); lines_it++) {
        // Use a stringstream to extract the current origin vertex for this line.
        isstr = std::istringstream(*lines_it);
        auto origin_vertex = -1;
        isstr >> origin_vertex;

        // Create the adjacency list for the current vertex
        auto curr_adj_list = std::forward_list<int>();
        auto back = curr_adj_list.before_begin();

        auto adjacent_vertex = -1;
        while (isstr >> adjacent_vertex) {
            // While the stringstream can capture data,
            // append it to the current adjacency list.
            back = curr_adj_list.insert_after(back, adjacent_vertex);
        }
        
        // Once the adjacency list is fully populated,
        // add it to the graph.
        graph[origin_vertex] = curr_adj_list;
    }
}

bool graphType::isEmpty() const {
    return graph.empty();
}

size_t graphType::size() const {
    return graph.size();
}

void graphType::clearGraph() {
    graph.clear();
}

void graphType::printGraph() const {
    std::cout << "Adjacency list of graph " << this << '\n';
    for (auto i = 0; i < size(); i++) {
        std::cout << std::setw(4) << '(' << i << "): { ";
        std::for_each(graph[i].begin(), graph[i].end(), [&](int v) {
                    std::cout << v << ' ';
                });
        std::cout << " }\n";
    }
    std::cout << '\n';
}

graphType::graphType(int size) {
    //graph.resize(size);
}

graphType::~graphType() {
    clearGraph();
}

void graphType::dft(int v, std::vector<bool> &visited) {
    // visit the vertex
    std::cout << v << ' ';
    visited[v] = true;
    
    for (auto graphIt = graph[v].begin();
         graphIt != graph[v].end();
         ++graphIt) {
        int w = *graphIt;
        if (!visited[w]) {
            dft(w, visited);
        }
    }
}

void graphType::depthFirstTraversal() {
    auto visited = std::vector<bool>(size());
    
    std::cout << "DFS: { ";
    for (auto index = 0; index < size(); index++) {
        if (!visited[index]) {
            dft(index, visited);
        }
    }
    std::cout << "}\n";
}

void graphType::dftAtVertex(int vertex) {
    auto visited = std::vector<bool>(size());
    std::cout << "(from vertex " << vertex << ") ";
    dft(vertex, visited);
}

void graphType::breadthFirstTraversal() {
    auto queue = std::queue<int>();
    auto visited = std::vector<bool>(size());

    std::cout << "BFS: { ";

    for (auto index = 0; index < size(); index++) {
        if (!visited[index]) {
            queue.push(index);

            // visit the vertex
            visited[index] = true;
            std::cout << index << ' ';

            while (!queue.empty()) {
                auto u = queue.front();
                queue.pop();

                for (auto w : graph[u]) {
                    if (!visited[w]) {
                        queue.push(w);

                        // visit the vertex
                        std::cout << w << ' ';
                        visited[w] = true;
                    }
                }
            }
        }
    }

    std::cout << "}\n";
}

