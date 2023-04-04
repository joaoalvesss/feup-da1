#include "../headers/menu.h"
#include <iostream>

bool Menu::exitApplication;
Graph Menu::graph;

Menu::Menu(){
    graph = *new Graph();
    exitApplication = false;
    utils::readCsvData(graph);
}
void Menu::init() {
    std::atexit(finish);

    while (!exitApplication) {
        int option = showMenu();

        switch (option) {
            case 0:
                exitApplication = true;
                break;

            case 1:
            {
                std::string src;

                std::cout << "Enter the src: ";
                std::cin >> std::ws;
                std::getline(std::cin, src);

                std::string dest;

                std::cout << "Enter the dest: ";
                std::cin >> std::ws;
                std::getline(std::cin, dest);

                int train_num = graph.edmondsKarp(src, dest);

                if(train_num == -1){
                    std::cout << "Insert valid stations! " << src << " " << dest;
                } else if(train_num == -2){
                    std::cout << "There's no connection between the stations";
                } else{
                    std::cout << "The max number of trains that can simultaneously travel between the stations is: " << train_num << '\n';
                }
                break;
            }
            case 2:
            {
                int aux;
                std::vector<pair<pair<std::string, std::string>, int>> value = graph.findMostTrainsRequired();
                for(const auto &pair : value){
                    cout << "{" << pair.first.first << "->" << pair.first.second << "}\n";
                    aux = pair.second;
                }
                cout << "Number of trains: " << aux;
                break;
            }
            case 3:
            {
                std::string answer;
                bool district;
                int k;

                cout << "Want to see districts? Enter exactly yes or no:";
                std::cin >> std::ws;
                std::getline(std::cin, answer);


                if(answer == "yes") district = true;
                else district = false;

                cout << "\n How many do you want to see?";
                std::cin >> k;

                for(const auto &value : graph.topKPlaces(k, district)){
                    cout << value.s << " - " << value.i << "\n";
                }
            }
                break;

            case 4:
            {
                std::string station;

                std::cout << "Station name:";
                std::cin >> std::ws;
                std::getline(std::cin, station);

                cout << "The maximum number of trains in [" << station << "] is [" << graph.findMaxStationTrains(station) << "]\n";
                break;
            }

            case 5:
            {
                std::string src;

                std::cout << "Enter the src: ";
                std::cin >> std::ws;
                std::getline(std::cin, src);

                std::string tgt;

                std::cout << "Enter the dest: ";
                std::cin >> std::ws;
                std::getline(std::cin, tgt);

                std::pair<double,double> aux = graph.maxTrainsMinCost(src, tgt);
                cout << "Max flow from " << src << " to " << tgt << " costs " << aux.first << " with flow " << aux.second;
                break;
            }

            case 6:
                break;

            case 7:
                break;

            case 8:
                break;

            case 9:
                break;

            default:
                std::cout << "Please choose a valid option.\n";
                break;
        }
    }
}

int Menu::showMenu() {
    int choice;

    std::cout << "\n\n";
    std::cout << "-------------------------- MAIN MENU ---------------------------\n";
    std::cout << "[0] Quit\n";
    std::cout << "[1] Maximum number of trains that can travel between two stations\n";
    std::cout << "[2] Pairs of stations that require the most trains (takes ~ 30s)\n";
    std::cout << "[3] Top K Places // REVIEW THIS\n";
    std::cout << "[4] Maximum number of trains in a stations at the time\n";
    std::cout << "[5] Travel trains simultaneously with min cost to company\n";
    std::cout << "[6] Max travel trains simultaneously with reduced connectivity\n";
    std::cout << "[7] Top K most affected stations by each segment failure\n\n";

    std::cout << "\tEnter your choice: ";
    std::cin >> choice;

    if (!std::cin) { exit(0);}


    std::cout.flush();
    std::cout << "\n";
    std::cout.flush();

    return choice;
}

void Menu::finish() {
    std::cout << "Finishing execution.\n";
}