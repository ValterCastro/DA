//
// Created by Válter Castro on 16/05/2024.
//

#ifndef DA2_MENU_H
#define DA2_MENU_H

#include "Graph.h"

typedef enum {
    Nodes = 1,
    Edges = 2,
    Both = Nodes | Edges
} GraphType;

class Menu{
private:
    int ReadGraph(const std::string &graph, GraphType type);
    void ReadToyGraphMenu();
    void ReadRealWorldGraphMenu();
    void ReadExtraGraphMenu();
    void AlgorithmMenu();
public:


    Graph* graph = new Graph();
    Menu();
    int ReadMenu();
};

#endif //DA2_MENU_H
