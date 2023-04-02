#include "../headers/manager.h"

Manager::Manager() {
    this->graph = new Graph();
    utils::readCsvData(*(graph));
}