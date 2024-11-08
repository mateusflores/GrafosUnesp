#include "Graph.h"



int main(int argc, char *argv[]) {
    double prob;
    int qtNodes = 0; 

    prob = std::stod(argv[1]); 
    qtNodes = std::stoi(argv[2]);

    Graph *g = new Graph();

    g->initializeAdjVector(qtNodes);

    g->erdosRenyi(prob, qtNodes);

    cout << "Lista de adjacencias:" << endl;
    g->displayAdjList();

    return 0;
}