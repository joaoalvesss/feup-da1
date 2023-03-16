#ifndef PROJETO_1_VERTEXEDGE_H
#define PROJETO_1_VERTEXEDGE_H
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <string>

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(std::string name, std::string district, std::string municipality, std::string township, std::string line);

    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setVisited(bool visited);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double cap, std::string &type);
    bool removeEdge(int destID); // TODO

protected:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;

    // outgoing and coming edges
    std::vector<Edge *> adj;
    std::vector<Edge *> incoming;

    // auxiliary fields
    bool visited = false;
    double dist = 0;
    Edge *path = nullptr;

};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double capacity, std::string &service_type);

    Vertex * getDest() const;
    double getCapacity() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest;
    double capacity;
    std::string service_type;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow = 0;
};

#endif //PROJETO_1_VERTEXEDGE_H
