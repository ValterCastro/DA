#include "../Include/Gestor.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Gestor::Gestor()= default;

/**
 * This function reads a CSV file and populates a graph with vertices and bidirectional edges.
 * The function can handle two types of CSV files: one with only vertices and edges and one with additional labels.
 * Complexity is O(n) where n is the number of lines in the file.
 *
 * @param filename The name of the file to read.
 */
void Gestor::read1File(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File could not be open" << endl;
    }

    string line;

    if (filename.find("Toy-Graphs") != string::npos) {
        getline(file, line);
    }

    if (filename != "../Toy-Graphs/tourism.csv") {
        while (getline(file, line)) {
            stringstream iss(line);
            string origemS, destinoS, distanciaS;

            getline(iss, origemS, ',');
            getline(iss, destinoS, ',');
            getline(iss, distanciaS, ',');

            int origem = stoi(origemS);
            int destino = stoi(destinoS);
            double distancia = stof(distanciaS);

            if (!graph.findVertex(origem)) {
                Vertex vertex1 = Vertex(origem);
                graph.addVertex(vertex1.getId());
            }
            if (!graph.findVertex(destino)) {
                Vertex vertex2 = Vertex(destino);
                graph.addVertex(vertex2.getId());
            }

            graph.addBidirectionalEdge(origem, destino, distancia);
        }
    } else {
        while (getline(file, line)) {
            stringstream iss(line);
            string origemS, destinoS, distanciaS, labelOrigem, labelDestino;

            getline(iss, origemS, ',');
            getline(iss, destinoS, ',');
            getline(iss, distanciaS, ',');
            getline(iss, labelOrigem, ',');
            getline(iss, labelDestino, ',');

            int origem = stoi(origemS);
            int destino = stoi(destinoS);
            double distancia = stof(distanciaS);


            if (!graph.findVertex(origem)) {
                Vertex vertex1 = Vertex(origem, labelOrigem);
                graph.addVertex(vertex1.getId());
            }
            if (!graph.findVertex(destino)) {
                Vertex vertex2 = Vertex(destino, labelDestino);
                graph.addVertex(vertex2.getId());
            }

            graph.addBidirectionalEdge(origem, destino, distancia);
        }
    }
}

/**
 * This function reads two CSV files to populate a graph with vertices and bidirectional edges.
 * The first file contains the nodes and the second one contains the edges. It also skips the header of each file.
 * It measures and prints the execution time.
 * Complexity is O(n+m) where n is the number of lines in the nodes file and m is the number of lines in the edges file.
 *
 * @param nodes The name of the file containing the nodes.
 * @param edges The name of the file containing the edges.
 */
void Gestor::read2Files(const string &nodes, const string &edges) {
    clock_t start = clock();

    ifstream nodesFile(nodes);
    ifstream edgesFile(edges);
    if(!nodesFile.is_open()) {
        cout << "File could not be open" << endl;
    }
    if(!edgesFile.is_open()) {
        cout << "File could not be open" << endl;
    }

    string line;
    getline(nodesFile, line); // skip the first line (column headers)

    while(getline(nodesFile,line)){
        stringstream iss(line);
        string idS, longitudeS, latitudeS;
        getline(iss,idS,',');
        getline(iss,longitudeS,',');
        getline(iss,latitudeS,',');

        int id = stoi(idS);
        double longitude = stof(longitudeS);
        double latitude = stof(latitudeS);
        Vertex v = Vertex(id,longitude,latitude);
        graph.addVertex(id,longitude,latitude);
    }


    getline(edgesFile, line); //skip the first line

    while(getline(edgesFile,line)){
        stringstream iss(line);
        string origemS, destinoS, distanciaS;

        getline(iss,origemS,',');
        getline(iss,destinoS,',');
        getline(iss,distanciaS,',');

        int origem = stoi(origemS);
        int destino = stoi(destinoS);
        double distancia = stof(distanciaS);
        graph.addBidirectionalEdge(origem, destino,distancia);
    }

    clock_t end = clock();
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

}

/**
 * This function applies the backtracking algorithm to the graph to solve the Travelling Salesman Problem (TSP).
 * It measures and prints the minimum cost and the execution time.
 * Complexity is O(n!) where n is the number of vertices in the graph.
 */
void Gestor::backtrack() {
    clock_t start = clock();

    double min_cost = numeric_limits<double>::max();
    vector<int> path = {0};
    vector<bool> visited(graph.getNumVertex(),false);
    visited[0] = true;

    graph.tsp_backtrack(path,visited,min_cost,0);

    clock_t end = clock();

    std::cout << "Minimum Distance: " << min_cost << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;


}
/**
 * This function applies the triangular approximation algorithm to the graph to solve the Travelling Salesman Problem (TSP).
 * It measures and prints the minimum distance and the execution time.
 * Complexity is O(n^2) where n is the number of vertices in the graph.
 */
void Gestor::triangular() {
    clock_t start = clock();

    double total = graph.triangularApproximation();

    clock_t end = clock();

    std::cout << "Minimum Distance: " << total << std::endl;
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}
/**
 * This function applies the nearest neighbor algorithm to the graph.
 * It measures and prints the minimum distance and the execution time.
 * Complexity is O(n^2) where n is the number of vertices in the graph.
 */
void Gestor::nearestNeighbor(){
    Vertex* initial = graph.findVertex(0);
    Vertex* current = graph.findVertex(0);
    vector<Edge*> path;
    double distance = 0.0;

    clock_t start = clock();

    graph.nearestNeighbor(initial,current,path,graph.getNumVertex(),distance,false);

    for(auto v: path){
        cout << v->getOrig()->getId() << " -> ";
    }
    Edge* last = path.back();
    cout << last->getDest()->getId() << endl;
    cout << "Minimum Distance: " <<distance << endl;
    clock_t end = clock();
    std::cout << "Execution Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}
void Gestor::menu() {
    while (true){
        cout << "--------------------------------------------------------\n";
        cout << "|          Urban Deliveries and Ocean Shipping         |\n";
        cout << "--------------------------------------------------------\n";
        cout << "| 1 - Read Toy-Graphs                                  |\n";
        cout << "| 2 - Read Extra_Fully_Connected_Graphs                |\n";
        cout << "| 3 - Read Real-world Graphs                           |\n";
        cout << "| 4 - BackTrack                                        |\n";
        cout << "| 5 - Triangular                                       |\n";
        cout << "| 6 - NearestNeighbor                                  |\n";
        cout << "--------------------------------------------------------\n";

        int opt;
        cout << "\nOption: ";
        cin >> opt;

        switch (opt) {
            case 1:
                int opt1;
                cout << "-------------------------------------------------------\n";
                cout << "| 1 - read shipping.csv                                |\n";
                cout << "| 2 - read stadiums.csv                                |\n";
                cout << "| 3 - read tourism.csv                                 |\n";
                cout << "-------------------------------------------------------\n";
                cout << "\nOption: ";
                cin >> opt1;
                switch (opt1) {
                    case 1:
                        read1File("../Toy-Graphs/shipping.csv");
                        menu();
                    case 2:
                        read1File("../Toy-Graphs/stadiums.csv");
                        menu();
                    case 3:
                        read1File("../Toy-Graphs/tourism.csv");
                        menu();
                }
            case 2:
                read1File("../Extra_Fully_Connected_Graphs/edges_500.csv");
                menu();
            case 3:
                int opt2;
                cout << "-------------------------------------------------------\n";
                cout << "| 1 - read graph 1                                     |\n";
                cout << "| 2 - read graph 2                                     |\n";
                cout << "| 3 - read graph 3                                     |\n";
                cout << "-------------------------------------------------------\n";
                cout << "\nOption: ";
                cin >> opt2;
                switch (opt2) {
                    case 1:
                        read2Files("../Real-world Graphs/graph1/nodes.csv","../Real-world Graphs/graph1/edges.csv");
                        menu();
                    case 2:
                        read2Files("../Real-world Graphs/graph2/nodes.csv","../Real-world Graphs/graph2/edges.csv");
                        menu();
                    case 3:
                        read2Files("../Real-world Graphs/graph3/nodes.csv","../Real-world Graphs/graph3/edges.csv");
                        menu();
                }
            case 4:
                backtrack();
                break;
            case 5:
                triangular();
                break;
            case 6:
                nearestNeighbor();
                break;
        }

    }
}


