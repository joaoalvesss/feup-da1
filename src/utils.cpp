#include <fstream>
#include "../headers/utils.h"
#include <iostream>
#include <cstdlib>

void utils::readCsvData(Graph &graph){
    std::ifstream stations("../resources/stations.csv");
    std::ifstream networks("../resources/network.csv");

    std::string line;
    int station_id = 0;

    getline(stations, line); // discard first line
    getline(networks, line); // discard first line

    while (getline(stations, line)) {
        std::stringstream ss(line);
        std::string name, district, municipality, township, train_line;

        getline(ss, name, ',');
        getline(ss, district, ',');
        getline(ss, municipality, ',');
        getline(ss, township, ',');
        getline(ss, line, '\n');

        if(!graph.addVertex(station_id, name, district, municipality, township, train_line)){
            std::cout << "Error inserting vertex with id: " << station_id << "\n";
            return;
        }
        station_id++;
    }

    while (getline(networks, line)) {
        std::stringstream ss(line);

        std::string station_a, station_b, capacity_string, service;

        getline(ss, station_a, ',');
        getline(ss, station_b, ',');
        getline(ss, capacity_string, ',');
        getline(ss, service, '\n');

        if(!graph.addEdge(station_a, station_b, std::stod(capacity_string), service)){
            std::cout << "Error inserting edge from: " << station_a << "to " << station_b << "\n";
        }
    }
}

void utils::continueOnENTER(){ // Does this work correctly?
    std::cout << "\nPress <Enter> to continue";
    while(std::cin.get() != '\n');
    std::cout << "\n\n";
}
