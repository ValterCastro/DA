//
// Created by Válter Castro on 16/05/2024.
//
#include "iostream"
#include "sstream"
#include "fstream"
#include "vector"
#include "Menu.h"

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
    cout << "| 0 - Exit                                                       |\n";
    cout << "------------------------------------------------------------------\n";

    int option;
    cin >> option;

    switch (option) {
        case 0:
            break;
        case 1:
            ReadGraphMenu();
        default:
            break;
    }

    return 0;
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

int Menu::ReadGraph(std::string graph) {

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
        for (const auto& col : row) {
            std::cout << col << " ";
        }
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
            ReadGraphMenu();
            break;
    }
    return 0;
}

void Menu::ReadGraphMenu() {
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
            ReadGraph(shipping);
            break;
        case 2:
            ReadGraph(stadiums);
            break;
        case 3:
            ReadGraph(tourism);
            break;
        case 4:
            ReadMenu();
        default:
            ReadGraphMenu();
            break;
    }
}