#ifndef PROJETO_1_UTILS_H
#define PROJETO_1_UTILS_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "graph.h"
#include "vertexEdge.h"

using namespace std;

namespace utils{
        void readCsvData(Graph &graph);
        void clearOnENTER();
}
#endif //PROJETO_1_UTILS_H
