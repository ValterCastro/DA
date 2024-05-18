#ifndef DA2_GESTOR_H
#define DA2_GESTOR_H



#include "../data_structures/Graph.h"

#include <string>
#include <iostream>

using namespace std;

class Gestor{
private:
    Graph graph;
    void readLine(string line);
    void read1File(const string &filename);
    void backtrack();
    void triangular();
    void nearestNeighbor();

    void read2Files(const string &nodes, const string &edges);

    unordered_map<int,int> um_nodes;
public:

    Gestor();
    void menu();

    void init();
};
#endif //DA2_GESTOR_H
