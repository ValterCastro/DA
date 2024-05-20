//
// Created by Válter Castro on 16/05/2024.
//

#ifndef DA2_MENU_H
#define DA2_MENU_H

#include "Graph.h"

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
    int ReadGraph(std::string graph, std::string type);
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
    /*!
     * \brief Function to display algorithms interface.
     * \param option To choose which algorithm.
     */
    void AlgorithmMenu(int option);


public:
    Graph* backtrack = new Graph();
    Graph* triangular_heuristic = new Graph();
    Graph* extra = new Graph();
    /*!
     * \brief Constructor for Menu💀.
     */
    Menu();
    int ReadMenu();
};

#endif //DA2_MENU_H
