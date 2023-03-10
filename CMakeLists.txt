cmake_minimum_required(VERSION 3.23)
project(Projeto_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projeto_1 main.cpp src/utils.cpp headers/utils.h headers/graph.h src/graph.cpp headers/vertexEdge.h src/vertexEdge.cpp)
