#include <iostream>
#include <fstream>
#include "Graph.h"

int main() {
    std::ifstream f("exemplo.dat");
    Graph *g = new Graph(f);
    g->printAdjMatrix();
    delete g;
}
