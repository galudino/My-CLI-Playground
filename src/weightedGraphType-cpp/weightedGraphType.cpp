/*!
    \file       weightedGraphType.cpp
    \brief      Source file

    \author
    \date
 */

#include "weightedGraphType.hpp"
#include <iostream>
#include <queue>
#include <cfloat>
#include <sstream>
#include <iomanip>

void weightedGraphType::createWeightedGraph() {
    auto infile = std::ifstream();
    auto filename = std::string();

    std::cout << "Enter input file name: ";
    std::cin >> filename;
    std::cout << std::endl;

    infile.open(filename);

    if (!infile) {
        std::cerr << "Unable to open file." << std::endl;
        return;
    }
    
    createWeightedGraph(infile);
}

void weightedGraphType::createWeightedGraph(const std::string &filename) {
    auto infile = std::ifstream();
    
    infile.open(filename);

    if (!infile) {
        std::cerr << "Unable to open file." << std::endl;
        return;
    }

    createWeightedGraph(infile);
    infile.close();
}

void weightedGraphType::createWeightedGraph(std::ifstream &infile) {
    if (!isEmpty()) {
        clearGraph();
    }
    
    // Create graph, as per graphType
    createGraph(infile);

    // Clear weight matrix/smallestWeight 
    if (!weights.empty()) {
        weights.clear();
    }
    
    if (!smallestWeight.empty()) {
        smallestWeight.clear();
    }

    if (!smallestWeights.empty()) {
        smallestWeights.clear();
    }
    
    // Adjust size of matrix
    // based on amount of vertices known.
    weights.resize(size());
    for (auto &row : weights) {
        row.resize(size());
    }
    
    // Adjust size of smallestWeight
    smallestWeight.resize(size());

    smallestWeights.resize(size());
    for (auto &row : smallestWeights) {
        row.resize(size());
    }
 
    // Store a vector of strings to store the remainder of infile,
    // line-by-line
    auto lines = std::vector<std::string>();
    
    // Capture the remainder of the file, line by line
    auto str = std::string(); 
    while (std::getline(infile, str)) {
        if (str.empty()) { break; }
        lines.push_back(str);
    }
    
    for (const auto &line : lines) {
        // Parse each line for the edge weight data.
        // The captured origin/destination_vertex values
        // will ensure that edge_weight is assigned to the
        // correct cell in the weight matrix.
        auto isstr = std::istringstream(line);

        auto origin_vertex = -1;
        auto destination_vertex = -1;
        auto edge_weight = -1.0;

        isstr >> origin_vertex;
        isstr >> destination_vertex;
        isstr >> edge_weight;
            
        weights[origin_vertex][destination_vertex] = edge_weight;
    }
}    

void weightedGraphType::printWeightMatrix() {
    std::cout << "Weight matrix of graph " << this << '\n';
    // Column indices
    for (auto i = 0; i < size(); i++) {
        std::cout << std::setw(10) << i;
    }
    std::cout << '\n';
    for (auto i = 0; i < size() * 10; i++) {
        std::cout << '-';
    }
    std::cout << '\n';

    auto i = 0;
    std::for_each(weights.begin(), weights.end(), [&i](const auto &row) {
        // Row index
        std::cout << i++;

        std::for_each(row.begin(), row.end(), [](double w) {
            std::cout << std::setw(9) << w << ' ';
        });
        std::cout << '\n';
    });

    std::cout << std::endl;
}

void weightedGraphType::shortestPath(int vertex) {
    for (auto u = 0; u < size(); u++) {
        smallestWeight[u] = weights[vertex][u];
    }

    auto weightFound = std::vector<bool>(size());

    weightFound[vertex] = true;
    smallestWeight[vertex] = 0.0;

    for (auto i = 0; i < size() - 1; i++) {
        auto minWeight = DBL_MAX;
        auto v = 0;

        for (auto j = 0; j < size(); j++) {
            if (!weightFound[j]) {
                if (smallestWeight[j] < minWeight) {
                    v = j;
                    minWeight = smallestWeight[v];
                }
            }
        }

        weightFound[v] = true;

        for (auto w = 0; w < size(); w++) {
            if (!weightFound[w]) {
                if (minWeight + weights[v][w] < smallestWeight[w]) {
                    smallestWeight[w] = minWeight + weights[v][w];
                }
            }
        }
    }
}

void weightedGraphType::shortestPaths() {
    for (auto vertex = 0; vertex < size(); vertex++) {
        shortestPath(vertex);
        smallestWeights[vertex] = smallestWeight;
        smallestWeight.clear();
    }
}

void weightedGraphType::printShortestPaths() {
    std::cout << "Shortest paths between all vertices of graph " << this << '\n';
    for (auto i = 0; i < size(); i++) {
        std::cout << std::setw(10) << i;
    }
    std::cout << '\n';
    for (auto i = 0; i < size() * 10; i++) {
        std::cout << '-';
    }
    std::cout << '\n';
    
    auto i = 0;
    std::for_each(smallestWeights.begin(), smallestWeights.end(), [&i](const auto &row) {
        std::cout << i++;
        std::for_each(row.begin(), row.end(), [](double w) {
            std::cout << std::setw(9) << w << ' ';
        });
        std::cout << '\n';
    });
    std::cout << std::endl;
}
 
void weightedGraphType::printShortestDistance(int vertex) {
    std::cout << "Shortest distances from origin vertex '" << vertex << "'" << std::endl;
    
    std::cout << "Vertex" << std::setw(15) << "Distance\n";
    for (auto vertex = 0; vertex < size(); vertex++) {
        std::cout << std::setw(4) << vertex 
                  << std::setw(12) << smallestWeight[vertex] << '\n';
    }

    std::cout << std::endl;
}

weightedGraphType::weightedGraphType(int size) : graphType(size) {

}

weightedGraphType::~weightedGraphType() {

}
