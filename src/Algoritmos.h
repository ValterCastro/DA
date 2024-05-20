#ifndef DA2_ALGORITMOS_H
#define DA2_ALGORITMOS_H

#include "Graph.h"

/*!
     * \brief Function that runs Prim algorithm.
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
     * \param mst mst edges.
     * \param root source node.
     * \return mst vertices.
     */
vector<Vertex*> dfsOnMst(const vector<Edge*> &mst, Vertex *root);
/*!
     * \brief Function that calculates total distance of a path in a graph.
     * \param path is the graph path.
     * \return total distance.
     */
double totalDistance(const vector<Vertex*> &path);
/*!
     * \brief Function that approximates the TSP algorithm with a MST.
     * \param graph is the graph.
     * \return solution.
     */
double triangularApproximation(Graph &graph);
/*!
     * \brief Function that calculates the nearest neighbor.
     * \param root is the vertex.
     * \return nearest neighbor dist.
     */
double nearestNeighbor(Vertex* root);

#endif //DA2_ALGORITMOS_H
