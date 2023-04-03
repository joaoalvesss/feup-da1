#include <fstream>
#include "../headers/utils.h"

std::string utils::replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::string utils::replaceAccents(std::string s) {
    s = replaceAll(s, "ã", "a");
    s = replaceAll(s, "á", "a");
    s = replaceAll(s, "à", "a");
    s = replaceAll(s, "â", "a");
    s = replaceAll(s, "é", "e");
    s = replaceAll(s, "ê", "e");
    s = replaceAll(s, "í", "i");
    s = replaceAll(s, "ó", "o");
    s = replaceAll(s, "õ", "o");
    s = replaceAll(s, "ô", "o");
    s = replaceAll(s, "ú", "u");

    s = replaceAll(s, "Ã", "A");
    s = replaceAll(s, "Á", "A");
    s = replaceAll(s, "À", "A");
    s = replaceAll(s, "Â", "A");
    s = replaceAll(s, "É", "E");
    s = replaceAll(s, "Ê", "E");
    s = replaceAll(s, "Í", "I");
    s = replaceAll(s, "Ó", "O");
    s = replaceAll(s, "Õ", "O");
    s = replaceAll(s, "Ô", "O");
    s = replaceAll(s, "Ú", "U");
    return s;
}


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

        if(line == "Rede Espanhola"){
            graph.addVertex(station_id, name, "", "", "", train_line);
            continue;
        }

        replaceAccents(name);
        replaceAccents(district);
        replaceAccents(municipality);
        replaceAccents(township);

        graph.addVertex(station_id, name, district, municipality, township, train_line);
        station_id++;
    }

    while (getline(networks, line)) {
        std::stringstream ss(line);

        std::string station_a, station_b, capacity_string, service;

        getline(ss, station_a, ',');
        getline(ss, station_b, ',');
        getline(ss, capacity_string, ',');
        getline(ss, service, '\n');

        graph.addBidirectionalEdge(station_a, station_b, std::stod(capacity_string), service);
    }
}

void utils::continueOnENTER(){
    std::cout << "\nPress <Enter> to continue";
    while(std::cin.get() != '\n');
    std::cout << "\n\n";
}
