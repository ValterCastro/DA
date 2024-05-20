cmake_minimum_required(VERSION 3.23)
project(DA2)

set(CMAKE_CXX_STANDARD 14)

include_directories(Include data_structures)

add_executable(DA2 main.cpp data_structures/Graph.cpp data_structures/VertexEdge.cpp src/Menu.cpp src/Algoritmos.cpp)
