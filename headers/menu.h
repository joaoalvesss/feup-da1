#ifndef PROJETO_1_MENU_H
#define PROJETO_1_MENU_H
#include "manager.h"

class Menu{
    static bool exitApplication;

public:
    static void init();
    static int showMenu();
    static void finish();
};
#endif //PROJETO_1_MENU_H
