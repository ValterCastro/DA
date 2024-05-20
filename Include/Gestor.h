#ifndef DA2_GESTOR_H
#define DA2_GESTOR_H



#include "../data_structures/Graph.h"

#include <string>
#include <iostream>

using namespace std;

class Gestor{
private:
    void readLine(string line);
    void read1File(const string &filename);
    void backtrack();
    void triangular();
    void nearestNeighbor();
    void tspNonFullyConnected(int startNode);

    void read2Files(const string &nodes, const string &edges);

    unordered_map<int,int> um_nodes;
public:
    Graph graph;

    Gestor();
    void menu();

    void init();
};
#endif //DA2_GESTOR_H
