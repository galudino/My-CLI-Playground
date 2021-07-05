/*!
    \file       weightedGraphType.hpp
    \brief      Header file

    \author
    \date
 */

#ifndef WEIGHTEDGRAPHTYPE_HPP
#define WEIGHTEDGRAPHTYPE_HPP

#include "graphType.hpp"
#include <vector>
#include <fstream>

class weightedGraphType : public graphType {
public:
    void createWeightedGraph();
    void createWeightedGraph(const std::string &filename);
    void createWeightedGraph(std::ifstream &infile);
    void printWeightMatrix();
    void shortestPath(int vertex);
    void shortestPaths();
    void printShortestDistance(int vertex);
    void printShortestPaths();

    weightedGraphType(int size = 0);
    ~weightedGraphType();
protected:
    std::vector<std::vector<double>> weights;
    std::vector<double> smallestWeight;
    std::vector<std::vector<double>> smallestWeights;
};

#endif /* WEIGHTEDGRAPHTYPE_HPP */

