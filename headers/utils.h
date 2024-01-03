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
        void continueOnENTER();
        std::string replaceAll(std::string str, const std::string& from, const std::string& to);
        std::string replaceAccents(std::string s);
}
#endif //PROJETO_1_UTILS_H
