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
                std::string dest;

                std::cout << "\t> Enter the source station:";
                std::cin >> std::ws;
                std::getline(std::cin, src);
                //std::cout << "\n";

                std::cout << "\t   > Enter the destiny station:";
                std::cin >> std::ws;
                std::getline(std::cin, dest);
                std::cout << "\n";

                int train_num = graph.edmondsKarp(src, dest);

                if(train_num == -1){
                    std::cout << "\t> Either one or both station dont exist!\n";
                } else if(train_num == -2){
                    std::cout << "\t> There's no connection between the stations,\n\t> so the flow between those stations is 0";
                } else{
                    std::cout << "\t> The maximum number of trains that can\n\t> simultaneously travel between the stations is " << train_num << '\n';
                }
                break;
            }
            case 2:
            {
                int aux;
                std::cout << "\t> Processing...\n\n";
                std::vector<pair<pair<std::string, std::string>, int>> value = graph.findMostTrainsRequired();
                for(const auto &pair : value){
                    cout << "\t> " << pair.first.first << " -> " << pair.first.second << "\n";
                    aux = pair.second;
                }
                cout << "\n\t> Maximum number of trains is " << aux << "\n";
                break;
            }
            case 3:
            {
                std::string answer;
                bool district;
                int k;

                std::cout << "\t> Do want to see districts or municipalities? D/m \n ";
                std::cout << "\t> ";
                std::cin >> std::ws;
                std::getline(std::cin, answer);

                if(answer == "D"){ district = true; }
                else { district = false; }

                std::cout << "\n";

                std::cout << "\t> How many do you want to see?\n";
                std::cout << "\t> ";
                std::cin >> k;


                std::vector<std::pair<std::string, double>> aux;
                std::string helper;
                if(district){ aux = graph.getMaxFlowPerDistrict(); helper = "districts"; }
                else{ aux = graph.getMaxFlowPerMunicipality(); helper = "municipalities"; }

                std::cout << "\n\t> The top-k " << helper << " to invest in:\n\n";
                if(district && (k > 18)) k = 18;
                else if(!district && (k > 136)) k = 136;
                for(int i = 0; i < k; i++){
                    if(!aux[i].first.empty()){
                        cout << "\t> " << i+1 << "o " << aux[i].first << " \n";
                    }
                    else continue;
                }
                break;
            }
            case 4:
            {
                std::string station;

                std::cout << "\t> Station name: ";
                std::cin >> std::ws;
                std::getline(std::cin, station);

                cout << "\n\t> The maximum number of trains in the " << station << " station is " << graph.findMaxStationTrains(station) << "\n";
                break;
            }

            case 5:
            {
                std::string src;
                std::string tgt;

                std::cout << "\t> Enter the source station: ";
                std::cin >> std::ws;
                std::getline(std::cin, src);

                std::cout << "\t   > Enter the destiny station: ";
                std::cin >> std::ws;
                std::getline(std::cin, tgt);
                std::cout << endl;

                std::pair<double,double> aux = graph.maxTrainsMinCost(src, tgt);
                cout << "\t> Max flow from " << src << " to " << tgt << " costs " << aux.first << " with flow " << aux.second << "\n";
                break;
            }

            case 6:
            {
                std::string src;
                std::string tgt;

                std::cout << "\t> Enter the source station: ";
                std::cin >> std::ws;
                std::getline(std::cin, src);

                std::cout << "\t   > Enter the destiny station: ";
                std::cin >> std::ws;
                std::getline(std::cin, tgt);
                std::cout << "\n";

                int i = graph.reducedConnectivity(src, tgt);
                if(i == -2){
                    std::cout << "\t> With this reduce connectivity there's\n\t> no longer a path between those station.\n";
                } else {
                    std::cout << "\t> Maximum flow from " << src << " to " << tgt << " with\n\t> reduced connectivity network is " << i << "\n";
                }
                break;
            }
            case 7:
            {
                int k;
                int q;

                std::cout << "\t> How many do you want to see? ";
                std::cin >> k;
                std::cout << "\n";

                std::cout << "\t> Sort by percentage of capacity lost\n\t> or total number of trains lost? 1/2: ";
                std::cin >> q;
                std::cout << "\n";

                vector<StringInt> v = graph.topKMostAffected(k, q);

                cout << "\t> The top-k stations affected by the reported failures are:\n";
                for (const StringInt& si : v) {
                    if (q == 1){
                        std::cout << "\n\t> The " << si.s << " station got its flow affected by " << si.i << "%";
                    }
                    else{
                        std::cout << "\n\t> The " << si.s << " station got its flow affected by " << si.i;
                    }
                }
                std::cout << "\n\n";
                break;
            }

            default:
                std::cout << "\t> Please choose a valid option.\n";
                break;
        }
    }
}

int Menu::showMenu() {
    int choice;

    std::cout << "\n\n";
    std::cout << "\t-------------------------- MAIN MENU ---------------------------\n";
    std::cout << "\t[0] Finish execution and quit\n";
    std::cout << "\t[1] Maximum number of trains that can travel between two stations\n";
    std::cout << "\t[2] Pairs of stations that handle the most trains (takes ~ 30s)\n";
    std::cout << "\t[3] Top-k districts or municipalities to invest more\n";
    std::cout << "\t[4] Maximum number of trains in a stations at the time\n";
    std::cout << "\t[5] Travel trains simultaneously with minimum company's cost\n";
    std::cout << "\t[6] Max travel trains simultaneously with reduced connectivity\n";
    std::cout << "\t[7] Top-k most affected stations by each segment failure\n";
    std::cout << "\t----------------------------------------------------------------\n\n";

    std::cout << "\t> Enter your choice: ";
    std::cin >> choice;

    if (!std::cin) { exit(0);}

    std::cout.flush();
    std::cout << "\n";
    std::cout.flush();

    return choice;
}

void Menu::finish() {
    std::cout << "\t> Finishing execution...\n";
}