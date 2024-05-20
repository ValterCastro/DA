#include "iostream"
#include "sstream"
#include "fstream"
#include "vector"
#include "Menu.h"
#include "Graph.h"
#include "Algoritmos.h"

using namespace std;

Menu::Menu() {
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
    cout << "| 3 - Read Extra-Graphs                                          |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 4 - Choose Algorithm                                           |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 0 - Exit                                                       |\n";
    cout << "------------------------------------------------------------------\n";

    int option;
    cin >> option;

    switch (option) {
        case 0:
            return 0;
        case 1:
            ReadToyGraphMenu();
            break;
        case 2:
            ReadRealWorldGraphMenu();
            break;
        case 3:
            ReadExtraGraphMenu();
            break;
        case 4:
            AlgorithmMenu();
            break;
        default:
            break;
    }

    return 0;
}

void Menu::ReadExtraGraphMenu() {

    std::string extra_nodes = "../Extra_Fully_Connected_Graphs/nodes.csv";
    std::string extra_edges_25 = "../Extra_Fully_Connected_Graphs/edges_25.csv";
    std::string extra_edges_50 = "../Extra_Fully_Connected_Graphs/edges_50.csv";
    std::string extra_edges_75 = "../Extra_Fully_Connected_Graphs/edges_75.csv";
    std::string extra_edges_100 = "../Extra_Fully_Connected_Graphs/edges_100.csv";
    std::string extra_edges_200 = "../Extra_Fully_Connected_Graphs/edges_200.csv";
    std::string extra_edges_300 = "../Extra_Fully_Connected_Graphs/edges_300.csv";
    std::string extra_edges_400 = "../Extra_Fully_Connected_Graphs/edges_400.csv";
    std::string extra_edges_500 = "../Extra_Fully_Connected_Graphs/edges_500.csv";
    std::string extra_edges_600 = "../Extra_Fully_Connected_Graphs/edges_600.csv";
    std::string extra_edges_700 = "../Extra_Fully_Connected_Graphs/edges_700.csv";
    std::string extra_edges_800 = "../Extra_Fully_Connected_Graphs/edges_800.csv";
    std::string extra_edges_900 = "../Extra_Fully_Connected_Graphs/edges_900.csv";


    cout << "------------------------------------------------------------------\n";
    cout << "| 1 - Read extra_edges_25                                        |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 2 - Read extra_edges_50                                        |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 3 - Read extra_edges_75                                        |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| X - Read extra_edges_X (100, 200, 300... 900)                  |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 0 - Go back                                                    |\n";
    cout << "------------------------------------------------------------------\n";


    ReadGraph(extra_nodes, Nodes);


    int option;
    cin >> option;

    switch (option) {
        case 0: return;
        case 1: {
            ReadGraph(extra_edges_25, Edges);
            break;
        } case 2: {
            ReadGraph(extra_edges_50, Edges);
            break;
        } case 3: {
            ReadGraph(extra_edges_75, Edges);
            break;
        } case 100: {
            ReadGraph(extra_edges_100, Edges);
            break;
        } case 200: {
            ReadGraph(extra_edges_200, Edges);
            break;
        } case 300: {
            ReadGraph(extra_edges_300, Edges);
            break;
        } case 400: {
            ReadGraph(extra_edges_400, Edges);
            break;
        } case 500: {
            ReadGraph(extra_edges_500, Edges);
            break;
        } case 600: {
            ReadGraph(extra_edges_600, Edges);
            break;
        } case 700: {
            ReadGraph(extra_edges_700, Edges);
            break;
        } case 800: {
            ReadGraph(extra_edges_800, Edges);
            break;
        } case 900: {
            ReadGraph(extra_edges_900, Edges);
            break;
        } default:
            break;

    }

    AlgorithmMenu();
}

void Menu::AlgorithmMenu() {
    cout << "------------------------------------------------------------------\n";
    cout << "|          Project II Ocean Shipping && Urban Deliveries         |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 1 - Backtracking                                               |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 2 - Triangular Approximation                                   |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 3 - Nearest Neighbor                                           |\n";
    cout << "------------------------------------------------------------------\n";
    cout << "| 0 - Exit                                                       |\n";
    cout << "------------------------------------------------------------------\n";



    int option;
    cin >> option;

    switch (option) {
        case 1: {
            clock_t start = clock();

            double res = backtrack(graph, graph.findVertex(0));

            clock_t end = clock();

            std::cout << "Minimum Distance: " << res << std::endl;
            std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
            break;
        } case 2: {
            clock_t start = clock();
            double total = triangularApproximation(graph);
            clock_t end = clock();

            std::cout << fixed << "Minimum Distance: " << total << std::endl;
            std::cout << fixed << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
            break;
        } case 3: {
            clock_t start = clock();
            double distance = nearestNeighbor(graph.findVertex(0));
            clock_t end = clock();

            cout << fixed << "Minimum Distance: " << distance << endl;
            std::cout << fixed << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
        } default:
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

int Menu::ReadGraph(std::string &graph, GraphType type) {
    std::ifstream file(graph);

    if (!file.is_open()) {
        std::cerr << "Unable to open file " << graph << std::endl;
        return 1;
    }
    std::string line;
    std::getline(file, line);
    std::vector<std::vector<std::string>> data;
    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        data.push_back(tokens);
    }

    file.close();

    switch (type) {
        case Nodes: {
            for (const auto &row: data)
                this->graph.addVertex(stoi(row[0]), stod(row[1]), stod(row[2]));
            break;
        } default: {
            if (type == Both) {
                set<int> vertices;
                for (const auto &row: data) {
                    vertices.insert(stoi(row[0]));
                    vertices.insert(stoi(row[1]));
                }

                for (int vertex: vertices) {
                    this->graph.addVertex(vertex);
                }
            }

            for (const auto& row : data)
                this->graph.addBidirectionalEdge(stoi(row[0]), stoi(row[1]), stod(row[2]));
        }
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

    switch (option){
        case 1:
            ReadGraph(graph1_nodes, Nodes);
            ReadGraph(graph1_edges, Edges);
            break;
        case 2:
            ReadGraph(graph2_nodes, Nodes);
            ReadGraph(graph2_edges, Edges);
            break;
        case 3:
            ReadGraph(graph3_nodes, Nodes);
            ReadGraph(graph3_edges, Edges);
            break;
        case 4:
            ReadMenu();
            break;
        default:
            ReadRealWorldGraphMenu();
            break;
    }

    AlgorithmMenu();
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
            ReadGraph(shipping, Both);
            break;
        case 2:
            ReadGraph(stadiums, Both);
            break;
        case 3:
            ReadGraph(tourism, Both);
            break;
        case 4:
            ReadMenu();
        default:
            ReadToyGraphMenu();
            break;
    }

    AlgorithmMenu();
}