#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <string>

using namespace std;
class Edge;


/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(int id);
    Vertex(int id,string label);
    Vertex(int id,double longitude,double latitude);

    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    double getLat() const;
    double getLon() const;


    std::vector<Edge *> getIncoming() const;

    void setId(int id);
    void setLabel(string label);
    void setLongitude(double longitude);
    void setLatitude(double latitude);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);

    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int id);
    std::vector<Edge*> getOutgoing(Vertex* v) const;


protected:
    int id;
    double longitude;
    double latitude;
    string label;
    std::vector<Edge *> adj;
    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming;


};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    void setSelected(bool selected);
    void setReverse(Edge *reverse);
protected:
    Vertex * dest;
    float weight;
    bool selected = false;
    Vertex *orig;
    Edge *reverse = nullptr;
};

