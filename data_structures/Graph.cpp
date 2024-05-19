// By: Gonçalo Leão

#include "Graph.h"
#include "MutablePriorityQueue.h"

const int Graph::getNumVertex() const {
    return vertexMap.size();
}

std::unordered_map<int, Vertex*> Graph::getVertexMap() const {
    return vertexMap;
}

/**
 * This function is used to find a vertex in the graph given its id.
 * It has a complexity of O(1).
 * @param id The id of the vertex to find.
 * @return A pointer to the vertex if found, nullptr otherwise.
 */
Vertex * Graph::findVertex(int id) const {
    auto it = vertexMap.find(id);
    if(it != vertexMap.end()){
        return it->second;
    }
    else{
        return nullptr;
    }
}

/**
 * This function is used to find the index of a vertex in the graph given its id.
 * It has a complexity of O(n) as it iterates over the vertex set.
 * @param id The id of the vertex to find.
 * @return The index of the vertex if found, -1 otherwise.
 */
int Graph::findVertexIdx(const int &id) const {
    int i = 0;
    for (auto it = vertexSet.begin(); it !=  vertexSet.end(); it++, ++i)
        if ((*it)->getId() == id)
            return i;
    return -1;
}
/**
 * This function is used to add a vertex to the graph given its id.
 * It has a complexity of O(1) as it uses a map for the lookup and insertion.
 * @param id The id of the vertex to add.
 * @return True if the vertex was added successfully, false if a vertex with the same id already exists.
 */
bool Graph::addVertex(int id) {
    if (findVertex(id) != nullptr)
        return false;
    auto *v = new Vertex(id);
    vertexSet.insert(v);
    vertexMap.insert({id,v});
    return true;
}
/**
 * This function is used to add a vertex to the graph given its id, longitude, and latitude.
 * It has a complexity of O(1) as it uses a map for the lookup and insertion.
 * @param id The id of the vertex to add.
 * @param longitude The longitude of the vertex to add.
 * @param latitude The latitude of the vertex to add.
 * @return True if the vertex was added successfully, false if a vertex with the same id already exists.
 */
bool Graph::addVertex(int id, double longitude, double latitude){
    if(findVertex(id) != nullptr){
        return false;
    }
    auto *v = new Vertex(id,longitude,latitude);
    vertexSet.insert(v);
    vertexMap.insert({id,v});
    return true;
}


/**
 * This function is used to add an edge to the graph given the ids of the source and destination vertices and the weight of the edge.
 * It has a complexity of O(1) as it uses a map for the lookup.
 * @param sourc The id of the source vertex.
 * @param dest The id of the destination vertex.
 * @param w The weight of the edge.
 * @return True if the edge was added successfully, false if either the source or destination vertex does not exist.
 */

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

double Graph::findOrCalculateDistance(int origem, int destino) {
    Vertex* v1 = findVertex(origem);
    Vertex* v2 = findVertex(destino);
    if (!v1 || !v2) return std::numeric_limits<double>::max();
    Edge* edge = nullptr;
    for (Edge* e : v1->getAdj()) {
        if (e->getDest() == v2) {
            edge = e;
            break;
        }
    }
    if (edge) return edge->getWeight();
    return haversine(v1->getLat(), v1->getLon(), v2->getLat(), v2->getLon());
}

double Graph::calculate_tsp(int node, int edge, std::vector<std::vector<double>>& dists) {
    if (dists[node][edge] != -1) return dists[node][edge];

    double ans = std::numeric_limits<double>::max();

    if (edge == (1 << getNumVertex()) - 1) {
        return findOrCalculateDistance(node, 0);
    }

    for (int i = 0; i < getNumVertex(); ++i) {
        if (!(edge & (1 << i))) {
            double tmp = findOrCalculateDistance(node, i) + calculate_tsp(i, edge | (1 << i), dists);
            ans = std::min(ans, tmp);
        }
    }

    return dists[node][edge] = ans;
}

double Graph::tspNonFullyConnected(int startNode) {
    int n = getNumVertex();
    std::vector<std::vector<double>> dists(n, std::vector<double>((1 << n), -1));
    return calculate_tsp(startNode, 1 << startNode, dists);
}


/**
 * This function is used to perform a DFS on the graph starting from a given vertex.
 * It has a complexity of O(V + E) where V is the number of vertices and E is the number of edges.
 * @param mst The minimum spanning tree to perform the DFS on.
 * @param v The vertex to start the DFS from.
 * @param visited A vector to keep track of the visited vertices.
 * @param path A vector to keep track of the path taken.
 */
void Graph::dfs(const vector<Edge*> &mst, Vertex* v, vector<bool> &visited, vector<int> &path){
    visited[v->getId()] = true;
    cout << v->getId() << "->";
    path.push_back(v->getId());
    for(const auto &e: mst){
        if(!visited[e->getDest()->getId()] && e->getOrig()->getId() == v->getId()){
            dfs(mst, e->getDest(), visited, path);
        }
    }
}
/**
 * This function implements Prim's algorithm to find a minimum spanning tree of the graph.
 * It maintains a priority queue of edges to visit in order of their weights.
 * Complexity: O(ElogE) where E is the number of edges in the graph.
 *
 * @return A vector of Edge pointers representing the edges included in the minimum spanning tree.
 */
vector<Edge*> Graph::prim(){
    vector<Edge*> mst;

    priority_queue<Edge*, vector<Edge*>, weightCompare> pq;

    Vertex* source = findVertex(0);

    vector<bool> visited(vertexMap.size(), false);

    for(const auto  &e: source->getAdj()){
        pq.push(e);
    }
    visited[source->getId()] = true;

    while(!pq.empty()){
        Edge* e = pq.top();
        pq.pop();
        Vertex *v = e->getDest();
        Vertex *u = e->getOrig();
        if(visited[v->getId()]){
            continue;
        }
        visited[v->getId()] = true;
        mst.push_back(e);
        for(const auto  &parent : vertexMap){
            if(parent.second == v){
                for(auto edge: parent.second->getAdj()){
                    if(!visited[edge->getDest()->getId()]){
                        pq.push(edge);
                    }
                }
            }
        }
    }


    return mst;
}
/**
 * This function finds the vertex with the minimum weight edge in the graph that is not yet included in the MST.
 * Complexity: O(V) where V is the number of vertices in the graph.
 *
 * @param weights A vector of edge weights.
 * @param inMST A vector indicating whether each vertex is in the MST.
 * @return The index of the vertex with the minimum weight edge not yet in the MST.
 */
int Graph::minWeight(vector<double> &weights,vector<bool> &inMST){
    double min = numeric_limits<double>::max();
    int minIndex = -1;

    for(int i = 0; i < weights.size(); i++){
        if(!inMST[i] && weights[i] < min){
            min = weights[i];
            minIndex = i;
        }
    }
    return minIndex;
}

/**
 * This function implements the backtracking for the traveling salesman problem.
 * It iteratively explores the graph, marks vertices as visited, and updates the path and minimum cost.
 * Complexity: O(n!) where n is the number of vertices. (since it explores all possible permutations of vertices)
 *
 * @param path A vector representing the current path.
 * @param visited A vector indicating whether each vertex has been visited.
 * @param min_cost A reference to the minimum cost found so far.
 * @param costSoFar The cost of the path so far.
 */
void Graph::tsp_backtrack(vector<int> &path, vector<bool>& visited, double &min_cost, double costSoFar){
    if(path.size() == vertexSet.size()){
        int start_vertex = path.front();
        int last_vertex = path.back();
        for (Edge *edge: (vertexMap.find(last_vertex))->second->getAdj()){
            if (edge->getDest()->getId() == start_vertex){
                double cost = costSoFar + edge->getWeight();
                min_cost = min(cost, min_cost);
                break;
            }

        }
        return;
    }

    int last_vertex = path.back();
    for(Edge *edge: (vertexMap.find(last_vertex))->second->getAdj()){
        if(!visited[edge->getDest()->getId()]){
            path.push_back(edge->getDest()->getId());
            visited[edge->getDest()->getId()] = true;

            tsp_backtrack(path,visited,min_cost,costSoFar + edge->getWeight());
            path.pop_back();
            visited[edge->getDest()->getId()] = false;
        }
    }
}

/**
 * This function checks if there exists an edge between two given vertices.
 * Complexity: O(E) where E is the number of edges from the first vertex.
 *
 * @param v1 The id of the first vertex.
 * @param v2 The id of the second vertex.
 * @return True if there is an edge between the two vertices, false otherwise.
 */
bool Graph::haveEdge(int v1, int v2){
    int index;


    for(auto edge : vertexMap.find(v1)->second->getAdj()){
        if(edge->getDest()->getId() == v2){
            return true;
        }
    }
    return false;
}

/**
 * This function computes the geographical distance between two points given their latitudes and longitudes using the Haversine formula.
 * Complexity: O(1)
 *
 * @param lat1, lon1 The latitude and longitude of the first point.
 * @param lat2, lon2 The latitude and longitude of the second point.
 * @return The geographical distance between the two points in meters.
 */
double Graph::haversine(double lat1, double lon1, double lat2, double lon2){

    double lat1Rad = lat1 * M_PI /180;
    double lon1Rad = lon1 * M_PI /180;
    double lat2Rad = lat2 * M_PI /180;
    double lon2Rad = lon2 * M_PI /180;

    double latDiff = lat2Rad -lat1Rad;
    double lonDiff = lon2Rad -lon1Rad;

    double a = sin(latDiff/2.00) * sin(latDiff/2.00) + cos(lat1Rad) * cos(lat2Rad) * sin(lonDiff/2.00) * sin(lonDiff/2.00);

    double c = 2.00 * atan2(sqrt(a), sqrt(1-a));

    double distance = 6371000.0 * c;

    return distance;
}

/**
 * This function calculates the total distance of a path given a sequence of vertices.
 * If an edge does not exist between two consecutive vertices, it estimates the distance using the Haversine formula.
 * Complexity: O(E) where E is the number of edges in the path.
 *
 * @param path A vector of vertices representing the path.
 * @return The total distance of the path.
 */
double Graph::totalDistance(const vector<int> &path){
    double total = 0.0;

    for(int i = 0; i < path.size() - 1; i++){
        int v1 = path[i];
        int v2 = path[i + 1];

        if(!haveEdge(v1,v2)){
            total += haversine(vertexMap[v1]->getLat(),vertexMap[v1]->getLon(),vertexMap[v2]->getLat(),vertexMap[v2]->getLon());
            continue;
        }
        for(auto edge: vertexMap[v1]->getAdj()){
            if(edge->getDest()->getId() == v2){
                total += edge->getWeight();
                break;
            }
        }
    }

    int final = path.back();
    if(!haveEdge(final,path[0])){
        total += haversine(vertexMap[final]->getLat(),vertexMap[final]->getLon(),vertexMap[path[0]]->getLat(),vertexMap[path[0]]->getLon());
    }else{
        for(auto edge: vertexMap[final]->getAdj()){
            if(edge->getDest()->getId() == path[0]){
                total += edge->getWeight();
                break;
            }
        }
    }

    return total;
}
/**
 * This function uses Prim's algorithm to find a minimum spanning tree, then performs a DFS to form a path.
 * It then computes and returns the total distance of this path. The path is also printed.
 * Complexity: O(ElogE) for Prim's and O(V+E) for DFS, where V is the number of vertices and E is the number of edges.
 *
 * @return The total distance of the resulting path.
 */
double Graph::triangularApproximation(){
    vector<int> path(vertexSet.size());
    vector<Edge*> mst = prim();

    vector<bool> visited(vertexMap.size(),false);
    stack<int> stack;
    dfs(mst, mst[0]->getOrig(), visited, path);


    cout << "0" << endl;

    double total = totalDistance(path);

    return total;

}
/**
 * This function implements the nearest neighbor heuristic for the traveling salesman problem.
 * It starts from an initial vertex and repeatedly visits the unvisited vertex that is closest to the current vertex.
 * Complexity: O(n^2) where n is the number of vertices.
 *
 * @param initial, current References to the initial and current Vertex objects.
 * @param path A vector of Edge pointers representing the path.
 * @param graphSize The number of vertices in the graph.
 * @param distance The total distance traveled so far.
 * @param all A boolean indicating if all vertices have been visited.
 * @return The total distance of the path.
 */
double Graph::nearestNeighbor(Vertex* &initial,Vertex* &current, vector<Edge*>& path, int graphSize, double &distance, bool all){
    int i = 0;
    for(auto v: vertexMap){
        if(v.second->isVisited()) i++;
    }
    if(i == graphSize) all = true;

    if(all){
        double dist = haversine(current->getLat(), current->getLon(),initial->getLat(),initial->getLon());
        distance += dist;
    }

    current->setVisited(true);

    Edge *min = nullptr;
    double minWeight = numeric_limits<double>::max();
    for(auto e: current->getAdj()){
        if(!e->getDest()->isVisited() && e->getWeight() < minWeight){
            min = e;
            minWeight = e->getWeight();
        }
    }

    if(min){
        distance += minWeight;
        path.push_back(min);
        current = min->getDest();
    }
    else return distance;

    return nearestNeighbor(initial,current,path,graphSize,distance,all);
}
/**
 * This function deletes a matrix of integers.
 * Complexity: O(n) where n is the number of rows in the matrix.
 *
 * @param m The matrix to delete.
 * @param n The number of rows in the matrix.
 */
void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}
/**
 * This function deletes a matrix of doubles.
 * Complexity: O(n) where n is the number of rows in the matrix.
 *
 * @param m The matrix to delete.
 * @param n The number of rows in the matrix.
 */
void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

