/*!
    \file       graphType.hpp
    \brief      Header file

    \author
    \date
 */

#ifndef GRAPHTYPE_HPP
#define GRAPHTYPE_HPP

#include <vector>
#include <forward_list>
#include <fstream>

class graphType {
public:
    bool isEmpty() const;
    size_t size() const;
    void createGraph();
    void createGraph(const std::string &filename);
    void createGraph(std::ifstream &infile);
    void clearGraph();
    void printGraph() const;
    void depthFirstTraversal();
    void dftAtVertex(int vertex);
    void breadthFirstTraversal();

    graphType(int size = 0);
    virtual ~graphType();
protected:
    std::vector<std::forward_list<int>> graph;
private:
    void dft(int v, std::vector<bool> &visited);
};

#endif /* GRAPHTYPE_HPP */

