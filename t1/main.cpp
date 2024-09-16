#include <iostream>
#include <fstream>
#include "Graph.h"

int main() {
    std::ifstream f("exemplo.dat");
    Graph *g = new Graph(f);
    g->generateAdjMatrix();
    g->printAdjMatrix();

    std::cout << std::endl << std::endl;

    g->initializeDistMatrix();
    g->floydWarshall();
    g->printDistMatrix();

    delete g;
}
