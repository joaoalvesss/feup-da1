#ifndef PROJETO_1_MENU_H
#define PROJETO_1_MENU_H

#include "graph.h"
#include "utils.h"

class Menu{
private:
    static bool exitApplication;
    static Graph graph;

public:
    Menu();
    static void init();
    static int showMenu();
    static void finish();
};
#endif //PROJETO_1_MENU_H
