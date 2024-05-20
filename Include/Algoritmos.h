#ifndef DA2_ALGORITMOS_H
#define DA2_ALGORITMOS_H

#include "Graph.h"

/*!
     * \brief Function that runs Prim algorithm.
     * The function has a time complexity of O(|V|^2), with V being the number of vertices in the graph
     * \param graph is the inoput graph.
     * \param root root node id.
     * \return resulting edges.
     */
vector<Edge*> prim(Graph &graph, int root);
/*!
     * \brief Function that calculates haversine distance between two nodes.
     * \param v1 vertex one.
     * \param v2 vertex two.
     * \return haversine distance.
     */
double haversine(Vertex *v1, Vertex *v2);
/*!
     * \brief Function that calculates minimum spanning tree.
     * It has a time complexity of O(V+E), with V and E being the number of vertices and edges in the graph, respectively
     * \param mst mst edges.
     * \param root source node.
     * \return mst vertices.
     */
vector<Vertex*> dfsOnMst(const vector<Edge*> &mst, Vertex *root);
/*!
     * \brief Function that calculates total distance of a path in a graph.
     * Time complexity of O(E), with E being the number of edges
     * \param path is the graph path.
     * \return total distance.
     */
double totalDistance(const vector<Vertex*> &path);
/*!
     * \brief Function that approximates the TSP algorithm with a MST.
     * It has a time complexity of O(|V|^2) given that between Prim's Algorithm and the DFS operation it performs, the former is the upper bound
     * \param graph is the graph.
     * \return solution.
     */
double triangularApproximation(Graph &graph);
/*!
     * \brief Function that calculates the nearest neighbor.
     * It has a time complexity of O(|V|^2), with V being the number of vertices.
     * \param root is the vertex.
     * \return nearest neighbor dist.
     */
double nearestNeighbor(Vertex* root);

/*!
     * \brief Function that calculates the nearest neighbor.
     * It has a time complexity of O(|V|^2), with V being the number of vertices.
     * \param g is the graph on which the algorithm will be performed.
     * \param start is th vertex from which the algorithm will start
     * \return nearest neighbor dist.
     */
double backtrack(Graph &g, Vertex *start);

#endif //DA2_ALGORITMOS_H
