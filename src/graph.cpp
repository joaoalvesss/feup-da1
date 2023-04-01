#include "../headers/graph.h"
#include "../headers/utils.h"

Graph::Graph(){}

int Graph::getNumVertex() const {
    return (int)vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const std::string &id) const {
    for (auto v : vertexSet)
        if (v->getName() == id)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return (int)i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id, const std::string &name, const std::string &district, const std::string & municipality, const std::string &township, const std::string &line) { // TODO
    if (findVertex(name) != nullptr)
        return false;
    auto * v = new Vertex(id, name, district, municipality, township, line);
    vertexSet.push_back(v);
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const std::string &source, const std::string &dest, double capacity, std::string service_type) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, capacity, service_type);
    return true;
}

bool Graph::addBidirectionalEdge(const std::string &source, const std::string &dest, double w, std::string &service_type) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, service_type);
    auto e2 = v2->addEdge(v1, w, service_type);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::resetVisits() {
    for(Vertex* v: vertexSet){
        (*v).setVisited(false);
    }
}
