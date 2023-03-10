#include <fstream>
#include "../headers/utils.h"

list<std::string> utils::file::readCsv(const std::string& fileName) {
    ifstream openFile(fileName);
    list<string> elements;
    string line;

    if (!openFile.is_open()) return elements;

    openFile.ignore(500, '\n');

    while(getline(openFile, line))
        elements.push_back(line);

    return elements;
}