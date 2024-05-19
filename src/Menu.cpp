//
// Created by Válter Castro on 16/05/2024.
//
#include "iostream"
#include "sstream"
#include "fstream"
#include "vector"
#include "Menu.h"
#include "Graph.h"

using namespace std;

Menu::Menu(){
    ReadMenu();
}

int Menu::ReadMenu() {
    cout << "------------------------------------------------------------------\n";
    cout << "|          Project II Ocean Shipping && Urban Deliveries         |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 1 - Read Toy-Graphs                                            |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 2 - Read Real-world-Graphs                                     |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 3 - Choose Algorithm                                           |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 0 - Exit                                                       |\n";
    cout << "------------------------------------------------------------------\n";

    int option;
    cin >> option;

    switch (option) {
        case 0:
            return 0;
            break;
        case 1:
            ReadToyGraphMenu();
            break;
        case 2:
            ReadRealWorldGraphMenu();
            break;
        case 3:
            AlgorithmMenu(option);
            break;
        default:
            break;
    }

    return 0;
}

void Menu::AlgorithmMenu(int option) {
    cout << "------------------------------------------------------------------\n";
    cout << "|          Project II Ocean Shipping && Urban Deliveries         |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 1 - BackTrack Algorithm                                        |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 2 - Triangular Heuristic Algorithm                             |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 0 - Exit                                                       |\n";
    cout << "------------------------------------------------------------------\n";


    cin >> option;

    switch (option) {
        case 0:
            break;
        case 1:
            //backtrack->calculate_tsp();
            break;
        case 2:
            break;
        default:
            break;
    }
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

int Menu::ReadGraph(std::string graph, std::string type) {

    std::ifstream file(graph);

    if (!file.is_open()) {
        std::cerr << "Unable to open file " << graph << std::endl;
        return 1;
    }
    std::string line;
    std::getline(file, line);
    std::vector<std::vector<std::string>> data;
    while(std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        data.push_back(tokens);
    }

    file.close();


    for (const auto& row : data) {
        int i = 0;
        int src = 0;
        int dest = 0;
        int triangle_id = 0;
        vector<int> aux;
        for (const auto& col : row) {
            if(type == "Toy"){
                if(graph == "../Toy-Graphs/shipping.csv" || graph == "../Toy-Graphs/stadiums.csv"){
                    if(i < 2){
                        backtrack->addVertex(stoi(col));
                        aux.push_back(stoi(col));
                    }
                    else{
                        backtrack->addEdge(aux[0],aux[1], stod(col));
                    }
                }
                else{
                    if(i == 0){
                        backtrack->addVertex(stoi(col));
                        aux.push_back(stoi(col));
                        src = stoi(col);
                    }
                    else if(i == 1){
                        backtrack->addVertex(stoi(col));
                        aux.push_back(stoi(col));
                        dest = stoi(col);
                    }
                    else if (i == 2){
                        backtrack->addEdge(aux[0],aux[1], stod(col));
                    }
                    else if (i == 3){
                        backtrack->findVertex(src)->setLabel(col);
                    }
                    else{
                        backtrack->findVertex(dest)->setLabel(col);
                    }

                }
            }
            else if(type == "Real-nodes"){
                if(i == 0){
                    triangular_heuristic->addVertex(stoi(col));
                    triangle_id = stoi(col);
                }
                else if(i == 1){
                    triangular_heuristic->findVertex(triangle_id)->setLongitude(stod(col));
                }
                else{
                    triangular_heuristic->findVertex(triangle_id)->setLatitude(stod(col));
                }

            }
            else if(type == "Real-edges"){
                if(graph == "../Real-world-Graphs/graph1/edges.csv"){
                    if(i < 2){
                        //backtrack->addVertex(stoi(col));
                        aux.push_back(stoi(col));
                    }
                    else{
                        triangular_heuristic->addEdge(aux[0],aux[1], stod(col));
                    }

                }
                else{
                    if(i < 2){
                        //backtrack->addVertex(stoi(col));
                        aux.push_back(stoi(col));
                    }
                    else{
                        triangular_heuristic->addEdge(aux[0],aux[1], stod(col));
                    }
                }
            }

            //std::cout << col << " ";
            ++i;
        }
        aux.clear();
        std::cout << std::endl;
    }


    cout << "------------------------------------------------------------------\n";
    cout << "| 1 - Go back                                                    |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| Continue                                                       |\n";
    cout << "------------------------------------------------------------------\n";

    int option;
    cin >> option;

    switch(option){
        case 1:
            ReadMenu();
            break;
        default:
            ReadMenu();
            break;
    }
    return 0;
}

void Menu::ReadRealWorldGraphMenu() {
    cout << "------------------------------------------------------------------\n";
    cout << "| 1 - Read Graph1                                                |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 2 - Read Graph2                                                |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 3 - Read Graph3                                                |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 4 - Go back                                                    |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| Continue                                                       |\n";
    cout << "------------------------------------------------------------------\n";


    std::string graph1_nodes = "../Real-world-Graphs/graph1/nodes.csv";
    std::string graph2_nodes = "../Real-world-Graphs/graph2/nodes.csv";
    std::string graph3_nodes = "../Real-world-Graphs/graph3/nodes.csv";
    std::string graph1_edges = "../Real-world-Graphs/graph1/edges.csv";
    std::string graph2_edges = "../Real-world-Graphs/graph2/edges.csv";
    std::string graph3_edges = "../Real-world-Graphs/graph3/edges.csv";

    int option;
    cin >> option;

    switch(option){
        case 1:
            ReadGraph(graph1_nodes, "Real-nodes");
            ReadGraph(graph1_edges, "Real-edges");
            break;
        case 2:
            ReadGraph(graph2_nodes, "Real-nodes");
            ReadGraph(graph2_edges, "Real-edges");
            break;
        case 3:
            ReadGraph(graph3_nodes, "Real-nodes");
            ReadGraph(graph3_edges, "Real-edges");
            break;
        case 4:
            ReadMenu();
        default:
            ReadRealWorldGraphMenu();
            break;
    }

}

void Menu::ReadToyGraphMenu() {
    //system("clear || cls");
    cout << "------------------------------------------------------------------\n";
    cout << "| 1 - Read shipping                                              |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 2 - Read stadiums                                              |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 3 - Read tourism                                               |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 4 - Go back                                                    |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| Continue                                                       |\n";
    cout << "------------------------------------------------------------------\n";

    std::string shipping = "../Toy-Graphs/shipping.csv";
    std::string stadiums = "../Toy-Graphs/stadiums.csv";
    std::string tourism = "../Toy-Graphs/tourism.csv";

    int option;
    cin >> option;

    switch(option){
        case 1:
            ReadGraph(shipping, "Toy");
            break;
        case 2:
            ReadGraph(stadiums, "Toy");
            break;
        case 3:
            ReadGraph(tourism, "Toy");
            break;
        case 4:
            ReadMenu();
        default:
            ReadToyGraphMenu();
            break;
    }
}