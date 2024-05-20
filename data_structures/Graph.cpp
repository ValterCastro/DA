#include "Graph.h"

size_t Graph::getNumVertex() const {
    return vertexMap.size();
}

std::unordered_map<int, Vertex*> Graph::getVertexMap() const {
    return vertexMap;
}

Vertex * Graph::findVertex(int id) const {
    auto it = vertexMap.find(id);
    if(it != vertexMap.end()){
        return it->second;
    }
    else{
        return nullptr;
    }
}

bool Graph::addVertex(int id) {
    if (findVertex(id) != nullptr)
        return false;
    auto *v = new Vertex(id);
    vertexSet.insert(v);
    vertexMap.insert({id,v});
    return true;
}

bool Graph::addVertex(int id, double longitude, double latitude){
    if(findVertex(id) != nullptr){
        return false;
    }
    auto *v = new Vertex(id,longitude,latitude);
    vertexSet.insert(v);
    vertexMap.insert({id,v});
    return true;
}



bool Graph::addEdge(int sourc, int dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(int sourc,int dest,double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}


