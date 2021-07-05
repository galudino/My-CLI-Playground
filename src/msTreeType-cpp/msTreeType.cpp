/*!
    \file       msTreeType.cpp
    \brief      Source file

    \author
    \date
 */

#include "msTreeType.hpp"
#include <iostream>
#include <cfloat>
#include <sstream>
#include <iomanip>

void msTreeType::createSpanningGraph() {
    auto infile = std::ifstream();
    auto fileName = std::string();
    
    std::cout << "Enter input file name: ";
    std::cin >> fileName;
    std::cout << std::endl;

    infile.open(fileName);

    if (!infile) {
        std::cerr << "Unable to open file." << std::endl;
        return;
    }

    createSpanningGraph(infile);
    infile.close();
}

void msTreeType::createSpanningGraph(const std::string &filename) {
    auto infile = std::ifstream();

    infile.open(filename);

    if (!infile) {
        std::cerr << "Unable to open file." << std::endl;
        return;
    }

    createSpanningGraph(infile);
    infile.close();
}

void msTreeType::createSpanningGraph(std::ifstream &infile) {
    if (!isEmpty()) {
        clearGraph();
    }
    
    // Create graph, as per graphType
    createGraph(infile);

    if (!weights.empty()) {
        weights.clear();
    }

    if (!edges.empty()) {
        edges.clear();
    }

    if (!edgeWeights.empty()) {
        edgeWeights.clear();
    }

    weights.resize(size());
    for (auto &row : weights) {
        row.resize(size());
    }

    auto lines = std::vector<std::string>();

    auto str = std::string();
    while (std::getline(infile, str)) {
        if (str.empty()) { break; }
        lines.push_back(str);
    }

    for (const auto &line : lines) {
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

void msTreeType::printWeightMatrix() {
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
   
void msTreeType::minimalSpanning(int sVertex) {
    auto startVertex = 0;
    auto endVertex = 0;

    auto minWeight = DBL_MIN;

    source = sVertex;

    auto mstv = std::vector<bool>(size());

    for (auto j = 0; j < size(); j++) {
        edges[j] = source;
        edgeWeights[j] = weights[source][j];
    }

    mstv[source] = true;
    edgeWeights[source] = 0;

    for (auto i = 0; i < size() - 1; i++) {
        minWeight = DBL_MAX;

        for (auto j = 0; j < size(); j++) {
            if (mstv[j]) {
                for (auto k = 0; k < size(); k++) {
                    if (!mstv[k] && weights[j][k] < minWeight) {
                        endVertex = k;
                        startVertex = j;
                        minWeight = weights[j][k];
                    }
                }
            }
        }

       mstv[endVertex] = true;
       edges[endVertex] = startVertex;
       edgeWeights[endVertex] = minWeight;
    }
} 

void msTreeType::printTreeAndWeight() {
    auto treeWeight = 0;
    
    std::cout << "Source vertex: " << source << '\n'
              << "Edges  Weight" << std::endl;

    for (auto j = 0; j < size(); j++) {
        if (edges[j] != j) {
            treeWeight = treeWeight + edgeWeights[j];
            std::cout << "(" << edges[j] << ", " << j << ") " << edgeWeights[j] 
                      << std::endl;
        }
    }

    std::cout << '\n' << "Minimum spanning tree weight: " << treeWeight << std::endl;
}

msTreeType::msTreeType(int size) : graphType(size) {

}

