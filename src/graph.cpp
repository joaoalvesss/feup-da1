#include "../headers/graph.h"
#include "../headers/utils.h"

Graph::Graph(){}

bool Graph::removeVertex(const int &id){
    int idx = findVertexIdx(id);
    if (idx == -1) return false;
    Vertex *vertex = vertexSet[idx];

    for (auto edge : vertex->getAdj()) {
        Vertex *destVertex = edge->getDest();
        destVertex->removeEdge(id);
    }
    for (auto edge : vertex->getIncoming()) {
        Vertex *origVertex = edge->getOrig();
        origVertex->removeEdge(id);
    }

    vertexSet.erase(vertexSet.begin() + idx);
    delete vertex;

    return true;
}

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
void Graph::addEdge(const std::string &source, const std::string &dest, double capacity, std::string service_type, int weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    v1->addEdge(v2, capacity, service_type, weight);
}

void Graph::addBidirectionalEdge(const std::string &source, const std::string &dest, double w, std::string &service_type, int weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    auto e1 = v1->addEdge(v2, w, service_type, weight);
    auto e2 = v2->addEdge(v1, w, service_type, weight);
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

double Graph::bottleneck(const std::string &source, const std::string &target) {
    resetVisits();
    resetFlows();

    edmondsKarp(source, target);

    double bottleneck = INF;
    Vertex *v = findVertex(target);
    while (v->getPath() != nullptr) {
        Edge *e = v->getPath();
        bottleneck = std::min(bottleneck, e->getCapacity() - e->getFlow());
        v = e->getOrig();
    }
    return bottleneck;
}

std::vector<std::pair<std::pair<std::string, std::string>, int>> Graph::findMostTrainsRequired(){ // O(V^4 * E^2)
    int most_trains_required = 0;
    int trains_num = -1;
    std::vector<std::pair<std::pair<std::string, std::string>, int>> stations;
    std::unordered_map<std::string, int> aux;

    for (int i = 0; i < vertexSet.size(); i++) {
        for (int j = i; j < vertexSet.size(); j++) {
            std::string const dest = vertexSet[i]->getName();
            std::string const source = vertexSet[j]->getName();

            if (aux.find(source + dest) != aux.end()) {
                trains_num = aux[source + dest];
            } else {
                trains_num = edmondsKarp(source, dest);
                aux[source + dest] = trains_num;
                aux[dest + source] = trains_num;
            }

            if (trains_num > most_trains_required) {
                stations.clear();
                stations.emplace_back(std::make_pair(source, dest), trains_num);
                most_trains_required = trains_num;
            } else if (trains_num == most_trains_required) {
                stations.emplace_back(std::make_pair(source, dest), trains_num);
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


int Graph::findMaxStationTrains(const std::string &station) { // SIUUUUUUUUUUUUU
    std::vector<Vertex *> sources;

    for (Vertex *const &v: vertexSet) {
        if (v->getAdj().size() == 1 && v->getName() != station) {
            sources.push_back(v);
        }
    }

    auto *superSource = new Vertex(-1, "super_source", "", "", "", "");
    vertexSet.push_back(superSource);

    for (Vertex *const &s: sources) {
        Edge *e = superSource->addEdge(s, INF, (string &) "", 0);
        s->getIncoming().push_back(e);
    }

    int maxFlow = edmondsKarp(superSource->getName(), station);

    for (Vertex *const &s: sources) { s->removeEdge(superSource->getId()); }

    vertexSet.pop_back();
    delete superSource;

    return maxFlow;
}

struct CompareVertexPointers {
    bool operator()(Vertex *v1, Vertex *v2) const {
        return v1->getDist() > v2->getDist();
    }
};

bool Graph::dijkstraShortestPath(const std::string &source, const std::string &target) {
    std::priority_queue<Vertex *, std::vector<Vertex *>, CompareVertexPointers> stations;

    for (Vertex *v: vertexSet) {
        v->setVisited(false);
        v->setDist(INF);
        v->setPath(nullptr);
    }

    findVertex(source)->setDist(0);
    stations.push(findVertex(source));

    while (!stations.empty()) {
        Vertex *top = stations.top();
        stations.pop();

        if (top->isVisited()) continue;
        top->setVisited(true);

        if (top->getName() == target) { break; }

        for (Edge *v: top->getAdj()) {
            Vertex *to = v->getDest();
            if (to->isVisited()) continue;

            std::string standard = "STANDARD";
            double cost = (*(v->getServiceType()) == standard ? 2 : 4) * (v->getCapacity() - v->getFlow());

            if (to->getDist() > top->getDist() + cost) {
                to->setDist(top->getDist() + cost);
                to->setPath(v);
                stations.push(to);
            }
        }
    }
    return findVertex(target)->isVisited();
}

std::pair<double, double> Graph::maxTrainsMinCost(const std::string& src, const std::string& tgt) { // 3.1, O(V * E^2)
    double f = INF;
    int cost = 0;
    if(!dijkstraShortestPath(src, tgt)) return {-1, -1};

    for (Vertex *v = findVertex(tgt); v->getPath() != nullptr; v = v->getPath()->getOrig()) {
        f = std::min(f, v->getPath()->getCapacity() - v->getPath()->getFlow());
    }

    for (Vertex *v = findVertex(tgt); v->getPath() != nullptr; v = v->getPath()->getOrig()) {
        if ((string) "STANDARD" != *(v->getPath()->getServiceType())) { cost += f * 4; }
        else { cost += f * 2; }
    }
    return {cost, f};
}

bool Graph::askForRemovedEdge(std::string &src, std::string &tgt) {
    std::string q;
    std::cout << "\t> Do you want to remove another network? Y/n: ";
    std::cin >> std::ws;
    std::getline(std::cin, q);

    if (q != (std::string)("Y")) { std::cout << "\n"; return false; }

    std::cout << "\n\t> Enter the first station: ";
    std::cin >> std::ws;
    std::getline(std::cin, src);

    std::cout << "\t  > Enter the second station: ";
    std::cin >> std::ws;
    std::getline(std::cin, tgt);
    std::cout << "\n";

    return true;
}

int Graph::reducedConnectivity(const std::string &source, const std::string &dest){ // 4.1 topic
    Graph g = Graph(*this);
    std::string remove_src;
    std::string remove_tgt;
    while (askForRemovedEdge(remove_src, remove_tgt)) {
        Vertex * v1 = g.findVertex(remove_src);
        Vertex * v2 = g.findVertex(remove_tgt);
        v1->removeEdge(v2->getId());
        v2->removeEdge(v1->getId());
    }
    return g.edmondsKarp(source, dest);
}

std::vector<StringInt> Graph::topKMostAffected(int k, int q) { // 4.2 topic
    Graph g = Graph(*this);
    std::string remove_src;
    std::string remove_tgt;

    while (askForRemovedEdge(remove_src, remove_tgt)) {
        Vertex *v1 = g.findVertex(remove_src);
        Vertex *v2 = g.findVertex(remove_tgt);
        v1->removeEdge(v2->getId());
        v2->removeEdge(v1->getId());
    }

    std::vector<StringInt> pre;

    for (auto v : vertexSet) {
        StringInt si;
        si.s = v->getName();
        si.i = findMaxStationTrains(v->getName());
        pre.push_back(si);
    }

    std::vector<StringInt> post;
    for (auto v : g.getVertexSet()) {
        StringInt si;
        si.s = v->getName();
        si.i = g.findMaxStationTrains(v->getName());
        post.push_back(si);
    }

    std::vector<StringInt> res;
    for (const StringInt& a : pre) {
        StringInt si;
        si.s = a.s;
        StringInt b;
        for (const StringInt& n : post) {
            if (n.s == a.s) {
                b = n;
                break;
            }
        }
        if (q == 1) si.i = 100 - (b.i * 100 / a.i);
        else si.i = a.i - b.i;
        res.push_back(si);
    }
    sort(res.end(), res.begin());

    while (res.size() > k) {
        res.pop_back();
    }

    return res;
}

std::vector<std::pair<std::string, double>> Graph::getMaxFlowPerDistrict() {
    std::unordered_map<std::string, double> districtFlowMap;

    for (auto vertex : vertexSet) {
        std::string district = vertex->getDistrict();
        if (districtFlowMap.find(district) == districtFlowMap.end()) {
            districtFlowMap[district] = 0;
        }
        for (auto edge : vertex->getAdj()) {
            if(vertex->getDistrict() == edge->getDest()->getDistrict()){
                districtFlowMap[district] += edmondsKarp(vertex->getName(), edge->getDest()->getName());
            }
        }
    }
    std::vector<std::pair<std::string, double>> districtFlowVec(districtFlowMap.begin(), districtFlowMap.end());
    std::sort(districtFlowVec.begin(), districtFlowVec.end(), [](auto& a, auto& b){ return a.second > b.second; });

    return districtFlowVec;
}

std::vector<std::pair<std::string, double>> Graph::getMaxFlowPerMunicipality(){
    std::unordered_map<std::string, double> municipalityFlowMap;

    for (auto vertex : vertexSet) {
        std::string municipality = vertex->getMunicipality();
        if (municipalityFlowMap.find(municipality) == municipalityFlowMap.end()) {
            municipalityFlowMap[municipality] = 0;
        }
        for (auto edge : vertex->getAdj()) {
            if(vertex->getMunicipality() == edge->getDest()->getMunicipality()){
                municipalityFlowMap[municipality] += edmondsKarp(vertex->getName(), edge->getDest()->getName());
            }
        }
    }
    std::vector<std::pair<std::string, double>> municipalityFlowVec(municipalityFlowMap.begin(), municipalityFlowMap.end());
    std::sort(municipalityFlowVec.begin(), municipalityFlowVec.end(), [](auto& a, auto& b){ return a.second > b.second; });

    return municipalityFlowVec;
}