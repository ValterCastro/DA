#pragma once

#include "Graph.h"

typedef enum {
    Nodes = 1,
    Edges = 2,
    Both = Nodes | Edges
} GraphType;
/*!
 * \class Menu
 * \brief Menu for user interface
 *
 * In this Menu graphs will be red and algorithm will run and display their results.
 */
class Menu{
private:
    /*!
     * \brief Function that reads graphs.
     * \param graph is the graph path.
     * \param type can be Toy Real-(nodes|edges) or Extra.
     * \return 0 for success otherwise some error occurred.
     */
    int ReadGraph(std::string &graph, GraphType type);
    /*!
     * \brief Function to display toy graphs interface.
     */
    void ReadToyGraphMenu();
    /*!
     * \brief Function to display real world graphs interface.
     */
    void ReadRealWorldGraphMenu();
    /*!
     * \brief Function to display extra graphs interface.
     */
    void ReadExtraGraphMenu();

public:
    Graph graph;
    /*!
     * \brief Function to display algorithms interface.
     * \param option To choose which algorithm.
     */
    void AlgorithmMenu();


public:
    /*!
     * \brief Constructor for Menu.
     */
    Menu();
    int ReadMenu();
};
