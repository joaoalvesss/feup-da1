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

    /*** Vertex - Stations ***/

class Vertex {
public:
    Vertex(int id, std::string name, std::string district, std::string municipality, std::string township, std::string line);

    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;
    std::string getName() const;
    std::string getDistrict() const;
    std::string getMunicipality() const;
    std::string getTownship() const;
    std::string getLine() const;
    int getId() const;

    void setId(int id);
    void setVisited(bool visited);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge *addEdge(Vertex *dest, double cap, std::string &type, int weight);
    bool removeEdge(int destID);

protected:

    int id;
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

    /*** Edge - Network ***/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double capacity, std::string &service_type, int weight);

    Vertex * getDest() const;
    double getCapacity() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;
    std::string* getServiceType() const;
    int getWeight() const;

    void setReverse(Edge *reverse);
    void setFlow(double flow);
    void setCapacity(int capacity);

protected:
    Vertex * dest;
    double capacity;
    std::string* service_type;
    int weight;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow = 0;
};

#endif //PROJETO_1_VERTEXEDGE_H
