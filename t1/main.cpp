#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

int main(int argc, char *argv[]) {
    std::string graphType;
    double prob;

    prob = std::stod(argv[1]);
    graphType = argv[2];

    std::cout << "Probabilidade: " << prob << std::endl;
    std::cout << "Tipo de Grafo: " << graphType << std::endl;
    std::cout << std::endl;

    std::ifstream f("exemplo.dat");
    Graph *g = new Graph(f);
    g->generateAdjMatrix();
    g->printAdjMatrix();

    std::cout << std::endl << std::endl;

    g->initializeDistMatrix();
    g->floydWarshall();
    g->printDistMatrix();

    std::cout << std::endl;
    std::cout << "Mean: " << g->calculateMean() << std::endl;
    std::cout << "Longest Path: " << g->findLongestPath() << std::endl;

    delete g;
}
