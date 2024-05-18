cmake_minimum_required(VERSION 3.23)
project(DA2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA2 main.cpp data_structures/Graph.h data_structures/Graph.cpp data_structures/Heap.cpp data_structures/Heap.h data_structures/MutablePriorityQueue.h data_structures/UFDS.cpp data_structures/UFDS.h data_structures/VertexEdge.cpp data_structures/VertexEdge.h Include/Gestor.h src/Gestor.cpp src/Menu.h src/Menu.cpp)
