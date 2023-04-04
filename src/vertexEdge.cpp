#include <utility>

#include "../headers/vertexEdge.h"

    /*** Vertex - Stations ***/

Vertex::Vertex(int id, std::string name, std::string district, std::string municipality, std::string township, std::string line){
    this->id = id;
    this->name = std::move(name);
    this->district = std::move(district);
    this->municipality = std::move(municipality);
    this->township = std::move(township);
    this-> line = std::move(line);
}

Edge * Vertex::addEdge(Vertex *dest, double cap, std::string &type, int weight) {
    auto newEdge = new Edge(this, dest, cap, type, weight);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

std::string Vertex::getName() const{
    return this->name;
}

std::string Vertex::getMunicipality() const {
    return this->municipality;
}

std::string Vertex::getDistrict() const {
    return this->district;
}

std::string Vertex::getTownship() const {
    return this->township;
}

std::string Vertex::getLine() const{
    return this->line;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

int Vertex::getId() const{
    return id;
}

void Vertex::setId(int id){
    this->id = id;
}

    /*** Edge - Network ***/

Edge::Edge(Vertex *orig, Vertex *dest, double capacity, std::string &service_type, int weight){
    this->orig = orig;
    this->dest = dest;
    this->capacity = capacity;
    this->service_type = &service_type;
    this->weight = weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getCapacity() const {
    return this->capacity;
}

std::string* Edge::getServiceType() const{
    return this->service_type;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

int Edge::getWeight() const {
    return weight;
}
