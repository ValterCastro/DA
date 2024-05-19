// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include "MutablePriorityQueue.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <set>
#include <cmath>

#include "VertexEdge.h"

class Graph {
public:
    Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(int id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(int id);
    bool addVertex(int id, double longitude, double latitude);

    void tsp_backtrack(vector<int> &path, vector<bool>& visited, double &min_cost, double costSoFar);
    double triangularApproximation();
    vector<Edge*> prim();
    int minWeight(vector<double> &weights,vector<bool> &inMST);
    void dfs(const vector<Edge*> &mst, Vertex* v, vector<bool> &visited, vector<int> &path);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    bool haveEdge(int v1, int v2);
    double totalDistance(const vector<int> &path);
    double nearestNeighbor(Vertex* &initial,Vertex* &current, vector<Edge*>& path, int graphSize, double &distance, bool all);
    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(int sourc,int dest,double w);
    bool addBidirectionalEdge(int sourc,int dest,double w);

    const int getNumVertex() const;
    std::unordered_map<int, Vertex*> getVertexMap() const;

    void tsp_backtrack(std::vector<int> &path, std::vector<bool>& visited, double &min_cost, double costSoFar);
    double calculate_tsp(int node, int edge, std::vector<std::vector<double>>& dists);
    double tspNonFullyConnected(int startNode);


protected:
    set<Vertex*> vertexSet;
    unordered_map<int,Vertex*> vertexMap;
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    double findOrCalculateDistance(int origem, int destino);

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;
};

class weightCompare{
public:
    bool operator()(const Edge* e1, const Edge* e2) const{
        return e1->getWeight() > e2->getWeight();
    }
};

#endif /* DA_TP_CLASSES_GRAPH */
