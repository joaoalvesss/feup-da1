#include <fstream>
#include "../headers/utils.h"


std::vector<std::string> utils::file::readStations(const std::string& fileName, Graph &graph) {
    ifstream openFile(fileName);
    std::vector<string> elements;
    string line;

    if (!openFile.is_open()) return elements;

    openFile.ignore(500, '\n');
    int id = 0;
    while(getline(openFile, line)) {
        id++;
        graph.addVertex(id);
    }
    return elements;
}

std::vector<std::string> utils::file::readNetwork(const std::string &fileName, Graph &graph) {
    ifstream openFile(fileName);
    std::vector<string> elements;
    string line;

    if (!openFile.is_open()) return elements;

    openFile.ignore(500, '\n');
    int id = 0;
    while(getline(openFile, line)) {
        id++;
        graph.addEdge(id);
    }
    return elements;
}