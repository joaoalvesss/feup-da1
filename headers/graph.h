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

    /**
     * @brief Runs an Edmonds-Karp algorithm to determine the maximum flow from the source node to the destination node.
     * @brief Time Complexity: O(V * E^2)
     * @param source Source vertex
     * @param dest Destination vertex
     * @return Maximum flow from source to destination
     */
    int edmondsKarp(const std::string &source, const std::string &dest); // 2.1 topic

    /**
     * @brief Finds a path from the source vertex to the destination vertex, using a residual graph.
     * @brief Time Complexity: O(V + E)
     * @param source Source vertex
     * @param dest Destination vertex
     * @return True if there is a path, false otherwise
     */
    bool findAugmentingPath(Vertex * source, Vertex * dest); // 2.1 topic

    /**
     * @brief edmondsKarp auxiliary function that finds paths for edmondsKarp with a implementation that finds the shortest paths with a bfs-like algorithm.
     * @brief Time Complexity: O(V^3 * E^2)
     * @return Vector containing pairs of stations that have the most maximum flow between them, as well as the maximum flow value.
     */
    std::vector<std::pair<std::pair<std::string, std::string>, int>> findMostTrainsRequired(); // 2.2 topic

    /**
     * @brief Returns a vector that has pairs of districts and their flow, sorted in descending order of flow.
     * @brief Time Complexity: O(V^2 * E^3)
     * @return Vector containing the every district sorted in descending order of its flow.
     */
    std::vector<std::pair<std::string, double>> getMaxFlowPerDistrict(); // 2.3 topic

    /**
     * @brief Returns a vector that has pairs of municipalities and their flow, sorted in descending order of flow.
     * @brief Time Complexity: O(V^2 * E^3)
     * @return Vector containing the every municipality sorted in descending order of its flow.
     */
    std::vector<std::pair<std::string, double>> getMaxFlowPerMunicipality(); // 2.3 topic

    /**
     * @brief Reports the maximum number of trains that can simultaneously arrive at a given station, taking into consideration the entire railway grid.
     * @brief Time Complexity: O(V * E^2)
     * @param station Destination station
     * @return Maximum amount of trains that can arrive at the destination station
     */
    int findMaxStationTrains(const std::string &station); // 2.4 topic

    /**
     * @brief Calculates the maximum amount of trains that can simultaneously travel between two specific stations with minimum cost for the company.
     * @brief Time Complexity: O(V^2 * E^3 * log V)
     * @param src Source node
     * @param tgt Target node
     * @return Pair containing the maximum amount of trains that can travel between the two given stations and the minimum cost of running them.
     */
    std::pair<double, double> maxTrainsMinCost(const std::string &src, const std::string &tgt); // 3.1 topic

    /**
     * @brief Creates a reduced connectivity network and runs the Edmonds-Karp Algorithm on it to find the maximum flow between two given nodes.
     * @brief Time Complexity: O(V * E^2)
     * @param source Source node
     * @param dest Destination node
     * @return Maximum flow between source and target in reduced connectivity network
     */
    int reducedConnectivity(const std::string &source, const std::string &dest); // 4.1 topic

    /**
     * @brief Auxiliary function that is used to create a reduced connectivity network. It asks the user for an edge to be removed and stores it in the input parameters.
     * @brief Time Complexity: O(1)
     * @param src Source node
     * @param tgt Target node
     * @return True if the user has chosen to remove an edge, false otherwise.
     */
    static bool askForRemovedEdge(std::string &src, std::string &tgt); // 4.1 topic

    /**
     * @brief Creates a reduced connectivity network and lists the stations that are most affected in by the lost connectivity, either by percentage of trains lost of total number of trains lost.
     * @brief Time Complexity: O(V^2 * E^2)
     * @param k Number of stations the report should have
     * @param q Determines whether the stations will be sorted by percentage of trains lost (1) or total number of trains lost (2)
     * @return Vector containing k stations sorted by descending order of the amount of trains they've lost in this reduced connectivity network
     */
    std::vector<StringInt> topKMostAffected(int k, int q); // 4.2 Topic

protected:

    std::vector<Vertex *> vertexSet;    // vertex set
    int findVertexIdx(const int &id) const;
};


#endif //PROJETO_1_GRAPH_H
