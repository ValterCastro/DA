#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <stack>
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
    Graph() = default;
    Vertex *findVertex(int id) const;
    bool addVertex(int id);
    bool addVertex(int id, double longitude, double latitude);

    bool haveEdge(int v1, int v2);
    bool addEdge(int sourc,int dest,double w);
    bool addBidirectionalEdge(int sourc,int dest,double w);

    size_t getNumVertex() const;
    std::unordered_map<int, Vertex*> getVertexMap() const;

protected:
    set<Vertex*> vertexSet;
    unordered_map<int, Vertex*> vertexMap;
};

