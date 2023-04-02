#include "../headers/menu.h"
#include <iostream>

bool Menu::exitApplication = false;

void Menu::init() {
    Manager manager = Manager();

    std::atexit(Menu::finish);

    while (!Menu::exitApplication) {
        int option = Menu::showMenu();

        switch (option) {
            case 0:
                Menu::exitApplication = true;
                break;

            case 1:
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

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

    std::cout << std::endl;
    std::cout << "\t--------------- MAIN MENU ---------------\n";
    std::cout << "\t[0] \n";
    std::cout << "\t[1] \n";
    std::cout << "\t[2] \n";
    std::cout << "\t[3] \n";
    std::cout << "\t[4] \n";
    std::cout << "\t[5] \n";
    std::cout << "\t[6] \n";
    std::cout << "\t[7] \n";
    std::cout << "\t[8] \n";
    std::cout << "\t[9] \n";

    std::cout << "\tEnter your choice: ";
    std::cin >> choice;

    if (!std::cin)
        exit(0);

    std::cout.flush();
    std::cout << "\n";
    std::cout.flush();

    return choice;
}

void Menu::finish() {
    cout << "Finishing execution.\n Press <Enter> to confirm";
    while(std::cin.get() != '\n');
}