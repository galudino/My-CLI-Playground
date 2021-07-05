/*!
    \file       msTreeType.hpp
    \brief      Header file

    \author
    \date
 */

#ifndef MSTREETYPE_HPP
#define MSTREETYPE_HPP

#include "graphType.hpp"
#include <vector>
#include <fstream>

class msTreeType : public graphType {
public:
    void createSpanningGraph();
    void createSpanningGraph(const std::string &filename);
    void createSpanningGraph(std::ifstream &infile);
    void printWeightMatrix();
    void minimalSpanning(int sVertex);
    void printTreeAndWeight();

    msTreeType(int size = 0);
protected:
    int source;
    std::vector<std::vector<double>> weights;
    std::vector<int> edges;
    std::vector<double> edgeWeights;
};

#endif /* MSTREETYPE_HPP */

