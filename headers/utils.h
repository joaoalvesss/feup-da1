#ifndef PROJETO_1_UTILS_H
#define PROJETO_1_UTILS_H

#include <string>
#include <list>
#include "graph.h"

using namespace std;

namespace utils::file {
        std::list<std::string> readStations(const std::string &fileName, Graph &graph);
        std::list<std::string> readNetwork(const std::string &fileName, Graph &graph);
}
#endif //PROJETO_1_UTILS_H
