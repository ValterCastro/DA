#include "Algoritmos.h"


vector<Edge*> prim(Graph &graph, int root){
    vector<Edge*> mst;

    auto cmp = [](Edge *left,  Edge *right)->bool { return left->getWeight() > right->getWeight(); };
    priority_queue<Edge*, vector<Edge*>, decltype(cmp)> pq(cmp);

    Vertex* source = graph.findVertex(root);
    for (auto &pair : graph.getVertexMap()) pair.second->setVisited(false);

    for (const auto &e: source->getAdj()) pq.push(e);
    source->setVisited(true);

    while (!pq.empty()){
        Edge* e = pq.top(); pq.pop();
        Vertex *v = e->getDest();
        if (v->isVisited()) continue;
        v->setVisited(true);
        mst.push_back(e);
        for (auto edge: v->getAdj())
            if (!edge->getDest()->isVisited())
                pq.push(edge);
    }

    return mst;
}


double haversine(Vertex *v1, Vertex *v2) {
    double latDiff = (v2->getLat() - v1->getLat()) * M_PI / 180;
    double lonDiff = (v2->getLon() - v1->getLon()) * M_PI / 180;

    double a = sin(latDiff / 2.00) * sin(latDiff/2.00) +
               cos(v1->getLat() * M_PI / 180) * cos(v2->getLat() * M_PI / 180) *
               sin(lonDiff/2.00) *sin(lonDiff/2.00);

    double c = 2.00 * atan2(sqrt(a), sqrt(1-a));

    double distance = 6371000.0 * c;

    return distance;
}

void dfsOnMstHelper(const vector<Edge*> &mst, Vertex *root, vector<Vertex*> &path) {
    root->setVisited(true);
    path.push_back(root);
    for (const auto &e: mst){
        if (!e->getDest()->isVisited() && e->getOrig() == root) {
            dfsOnMstHelper(mst, e->getDest(), path);
        }
    }
}

vector<Vertex*> dfsOnMst(const vector<Edge*> &mst, Vertex *root) {
    for (Edge *e : mst) {
        e->getOrig()->setVisited(false);
        e->getDest()->setVisited(false);
    }

    vector<Vertex*> path;
    dfsOnMstHelper(mst, root, path);

    return path;
}



double totalDistance(const vector<Vertex*> &path) {
    auto findEdge = [](Vertex *v1, Vertex *v2)->Edge* {
        Edge *ret = nullptr;
        for (Edge *cmp : v1->getAdj()) if (cmp->getDest() == v2) { ret = cmp; break; }
        return ret;
    };

    double total = 0.0;

    for (auto vertexItr = next(path.begin()); vertexItr != prev(path.end()); vertexItr++) {
        Vertex *v1 = *prev(vertexItr);
        Vertex *v2 = *vertexItr;

        Edge *common = findEdge(v1, v2);
        total += common  ? common->getWeight() : haversine(v1, v2);
    }

    Edge *common = findEdge(path.back(), path[0]);
    total += common ? common->getWeight() : haversine(path.back(), path[0]);

    return total;
}

double triangularApproximation(Graph &graph) {
    vector<Edge*> mst = prim(graph, 0);
    return totalDistance(dfsOnMst(mst, mst[0]->getOrig()));
}

double nearestNeighbor(Vertex* root) {
    auto getShortestUnvisitedEdge = [](const vector<Edge*> &adj)->Edge* {
        Edge *minEdge = nullptr;
        for (Edge *cmp : adj) {
            if (cmp->getDest()->isVisited()) continue;
            if (minEdge == nullptr) minEdge = cmp;
            else minEdge = min(minEdge->getWeight(), cmp->getWeight()) == cmp->getWeight() ? cmp : minEdge;
        }
        return minEdge;
    };

    Vertex *current = root;

    double distance = 0.0f;
    vector<Edge*> path;

    while (true) {
        current->setVisited(true);

        Edge *minEdge = getShortestUnvisitedEdge(current->getAdj());
        if (minEdge == nullptr) break;

        distance += minEdge->getWeight();
        path.push_back(minEdge);
        current = minEdge->getDest();
    }

    distance += haversine(current, root);

    std::cout << path[0]->getOrig()->getId();

    for (Edge *e : path) {
        std::cout << " -> " << e->getDest()->getId();
    }

    std::cout << std::endl;

    return distance;
}


void backtrackHelper(Vertex *current, size_t left, double &min) {
    if (current->getDist() > min) return;
    if (left == 0) { min = std::min(min, current->getDist()); return; }

    for (Edge *edge : current->getAdj()) {
        Vertex *v = edge->getDest();
        if (!v->isVisited()) {
            v->setVisited(true);
            v->setDist(current->getDist() + edge->getWeight());
            v->setPath(edge);

            backtrackHelper(v, left - 1, min);

            v->setVisited(false);
        }
    }

}

double backtrack(Graph &g, Vertex *start) {
    for (const auto &pair : g.getVertexMap()) {
        pair.second->setVisited(false);
        pair.second->setDist(0);
    }

    start->setVisited(true);

    double minDistance = numeric_limits<double>::max();
    backtrackHelper(start, g.getNumVertex() - 1, minDistance);
    return minDistance;
}