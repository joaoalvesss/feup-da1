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
    Vertex *findVertex(const int &id) const;
    bool addVertex(const int &id);

    bool addEdge(const int &sourc, const int &dest, double w);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

protected:
    std::vector<Vertex *> vertexSet;    // vertex set
    int findVertexIdx(const int &id) const;
};


#endif //PROJETO_1_GRAPH_H
