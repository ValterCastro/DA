#ifndef DA2_ALGORITMOS_H
#define DA2_ALGORITMOS_H

#include "Graph.h"

vector<Edge*> prim(Graph &graph, int root);
double haversine(Vertex *v1, Vertex *v2);
vector<Vertex*> dfsOnMst(const vector<Edge*> &mst, Vertex *root);
double totalDistance(const vector<Vertex*> &path);
double triangularApproximation(Graph &graph);
double nearestNeighbor(Vertex* root);

#endif //DA2_ALGORITMOS_H
