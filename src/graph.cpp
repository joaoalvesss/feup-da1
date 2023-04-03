#include "../headers/graph.h"
#include "../headers/utils.h"

Graph::Graph(){}

int Graph::getNumVertex() const {
    return vertexSet.size();
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
void Graph::addVertex(const int &id, const std::string &name, const std::string &district, const std::string & municipality, const std::string &township, const std::string &line) { // TODO
    auto * v = new Vertex(id, name, district, municipality, township, line);
    vertexSet.push_back(v);
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
void Graph::addEdge(const std::string &source, const std::string &dest, double capacity, std::string service_type) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    v1->addEdge(v2, capacity, service_type);
}

void Graph::addBidirectionalEdge(const std::string &source, const std::string &dest, double w, std::string &service_type) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    auto e1 = v1->addEdge(v2, w, service_type);
    auto e2 = v2->addEdge(v1, w, service_type);
    e1->setReverse(e2);
    e2->setReverse(e1);
}

void Graph::resetVisits() {
    for(Vertex* v: vertexSet){
        (*v).setVisited(false);
    }
}

void Graph::resetFlows(){
    for(Vertex* v: vertexSet){
        for(Edge* e: v->getAdj()){
            e->setFlow(0);
        }
    }
}

int Graph::edmondsKarp(const std::string &source, const std::string &dest){ // O(V * E^2)
    Vertex *s = findVertex(source);
    Vertex *d = findVertex(dest);

    if (s == nullptr || d == nullptr || s == d) { return -1; }

    resetFlows();
    double maxFlow = 0;

    while (findAugmentingPath(s, d)) {
        double minCapacity = std::numeric_limits<double>::max();

        // minimum flow
        for(Vertex* v = d; v != s;){
            Edge* e = v->getPath();
            if(e->getDest() == v){
                v = e->getOrig();
                minCapacity = std::min(minCapacity, e->getCapacity() - e->getFlow());
            }
            else {
                v = e->getDest();
                minCapacity = std::min(minCapacity, e->getFlow());
            }
        }

        // update path of flow
        for(Vertex * v = d; v != s;){
            Edge* e = v->getPath();
            if(e->getDest() == v){
                v = e->getOrig();
                e->setFlow(e->getFlow() + minCapacity);
            }
            else {
                v = e->getDest();
                e->setFlow(e->getFlow() - minCapacity);
            }
        }

        maxFlow += minCapacity;
    }

    if(maxFlow == 0) { return -2 ;}
    else { return (int)maxFlow; }
}

bool Graph::findAugmentingPath(Vertex * source, Vertex * dest){ // O(V + E)
    for (Vertex *v : vertexSet) {
        v->setVisited(false);
        v->setPath(nullptr);
    }

    std::queue<Vertex *> q;
    q.push(source);
    source->setVisited(true);

    while (!q.empty()) {
        Vertex *v = q.front();
        q.pop();
        for (Edge *e : v->getAdj()) {
            Vertex *w = e->getDest();
            double residualCapacity = e->getCapacity() - e->getFlow();
            if (!w->isVisited() && residualCapacity > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }

    return (dest->getPath() != nullptr);
}

std::map<std::pair<std::string, std::string>, int> Graph::findMostTrainsRequired(){ // O(V^4 * E^2)
    int most_trains_required = 0, trains_num;
    std::map<std::pair<std::string, std::string>, int> stations;

    for (int i = 0; i < vertexSet.size(); i++) {
        for (int j = i; j < vertexSet.size(); j++) {
            Vertex* const dest = vertexSet[i];
            Vertex* const source = vertexSet[j];
            if (dest != source) {
                trains_num = edmondsKarp(source->getName(), dest->getName());
                if (most_trains_required < trains_num) {
                    stations.clear();
                    stations[std::make_pair(source->getName(), dest->getName())] = trains_num;
                    most_trains_required = trains_num;
                }
                else if (most_trains_required == trains_num) {
                    stations[std::make_pair(source->getName(), dest->getName())] = trains_num;
                }
            }
        }
    }
    return stations;
}

int stringInVector(const std::string& s, std::vector<std::string> v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == s) return i;
    }
    return -1;
}

std::vector<StringInt> Graph::topKPlaces(int k, bool district) { // REVER
    std::vector<StringInt> res;
    std::vector<std::string> names;
    std::vector<int> ints;
    std::string d;
    for (auto v : vertexSet) {
        if (district) d = v->getDistrict();
        else d = v->getMunicipality();
        int i = stringInVector(d, names);
        for (auto e : v->getAdj()) {
            if (i > -1) {
                ints[i] += e->getCapacity();
            }
            else {
                names.push_back(d);
                ints.push_back(e->getCapacity());
            }
        }
    }
    for (int i = 0; i < names.size(); i++){
        StringInt a = *new StringInt();
        a.i = ints[i];
        a.s = names[i];
        res.push_back(a);
    }
    sort(res.begin(), res.end());
    while (res.size() > k) {
        res.pop_back();
    }
    return res;
}


int Graph::findMaxStationTrains(const std::string &station) {
    int maxTrains = 0;
    for (Vertex *v : vertexSet) {
        for (Edge *e : v->getIncoming()) {
            if (e->getDest()->getName() == station) {
                double capacity = e->getCapacity();
                for (Edge *f : e->getOrig()->getIncoming()) {
                    if (f->getDest() == v) {
                        capacity = std::min(capacity, f->getCapacity());
                        break;
                    }
                }
                maxTrains = std::max(maxTrains, (int) capacity);
            }
        }
    }
    return maxTrains;
}

