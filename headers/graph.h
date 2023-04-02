#ifndef PROJETO_1_GRAPH_H
#define PROJETO_1_GRAPH_H
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#include "VertexEdge.h"

class Graph {
public:
    Graph();
    Vertex *findVertex(const std::string &id) const;
    bool addVertex(const int &id, const std::string &name, const std::string &district, const std::string & municipality, const std::string &township, const std::string &line);

    bool addEdge(const std::string &source, const std::string &dest, double capacity, std::string service_type);
    bool addBidirectionalEdge(const std::string &source, const std::string &dest, double w, std::string &service_type);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
    void resetVisits();
    void resetFlows();

    int edmondsKarp(const std::string &source, const std::string &dest);
    bool findAugmentingPath(Vertex * source, Vertex * dest);
protected:
    std::vector<Vertex *> vertexSet;    // vertex set
    int findVertexIdx(const int &id) const;
};


#endif //PROJETO_1_GRAPH_H
