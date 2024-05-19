//
// Created by Válter Castro on 16/05/2024.
//

#ifndef DA2_MENU_H
#define DA2_MENU_H

#include "Graph.h"

class Menu{
private:
    int ReadGraph(std::string graph, std::string type);
    void ReadToyGraphMenu();
    void ReadRealWorldGraphMenu();
    void AlgorithmMenu(int option);


public:
    Graph* backtrack = new Graph();
    Graph* triangular_heuristic = new Graph();
    Menu();
    int ReadMenu();
};

#endif //DA2_MENU_H
