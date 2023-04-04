#ifndef PROJETO_1_GRAPH_H
#define PROJETO_1_GRAPH_H
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_map>
#include "VertexEdge.h"

struct StringInt {
    std::string s;
    int i;

    bool operator<(StringInt &a) const {
        return i > a.i;
    }
};

class Graph {
public:
    Graph();
    Vertex *findVertex(const std::string &id) const;
    void addVertex(const int &id, const std::string &name, const std::string &district, const std::string & municipality, const std::string &township, const std::string &line);
    bool removeVertex(const int &id);

    void addEdge(const std::string &source, const std::string &dest, double capacity, std::string service_type, int weight);
    void addBidirectionalEdge(const std::string &source, const std::string &dest, double w, std::string &service_type, int weight);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
    void resetVisits();
    void resetFlows();

    int edmondsKarp(const std::string &source, const std::string &dest); // 2.1 topic
    bool findAugmentingPath(Vertex * source, Vertex * dest); // 2.1 topic
    std::vector<std::pair<std::pair<std::string, std::string>, int>> findMostTrainsRequired(); // 2.2 topic
    std::vector<StringInt> topKPlaces(int k, bool district);

    int findMaxStationTrains(const std::string &station); // 2.4 topic

    std::pair<double, double> maxTrainsMinCost(const std::string &src, const std::string &tgt); // 3.1 topic
    bool dijkstraShortestPath(const std::string &source, const std::string &target);

    int reducedConnectivity(const std::string &source, const std::string &dest); // 4.1 topic
protected:

    std::vector<Vertex *> vertexSet;    // vertex set
    int findVertexIdx(const int &id) const;
};


#endif //PROJETO_1_GRAPH_H
