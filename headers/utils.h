#ifndef PROJETO_1_UTILS_H
#define PROJETO_1_UTILS_H

#include <string>
#include <list>
#include "../headers/graph.h"
#include "../headers/vertexEdge.h"

using namespace std;

namespace utils::file {
        std::vector<std::string> readStations(const std::string &fileName, Graph &graph);
        std::vector<std::string> readNetwork(const std::string &fileName, Graph &graph);
}
#endif //PROJETO_1_UTILS_H
