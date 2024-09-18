#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

// ./main 0.5 50 er
int main(int argc, char *argv[]) {
    std::string graphType;
    double prob;
    int qtNodes = 0;    

    prob = std::stod(argv[1]);
    qtNodes = std::stoi(argv[2]);
    graphType = argv[3];

    std::cout << "Probabilidade: " << prob << std::endl;
    std::cout << "Quantidade de nós: " << qtNodes << std::endl;
    std::cout << "Tipo de Grafo: " << graphType << std::endl;
    std::cout << std::endl;

    /*
    // Inicializar com arquivo 
    // std::ifstream f("exemplo.dat");
    // Graph *g = new Graph(f);
    */

    // Cria um grafo vazio
    Graph *g = new Graph();

    if(graphType == "er"){
        // grafo de erdos renyi apenas
        for(int i = 0; i < qtNodes; i++){
            g->addNode(i);
        }
        g->initializeAdjMatrix(qtNodes);
        g->erdosRenyi(prob, qtNodes);
        g->printAdjMatrix();
        std::cout << std::endl << std::endl;
        g->initializeDistMatrix();
        g->floydWarshall();
        g->printDistMatrix();
    }
    else if (graphType == "ba"){
        // grafo de BA
        for(int i = 0; i < 20; i++){
            g->addNode(i);
        }
        g->initializeAdjMatrix(qtNodes);
        g->erdosRenyi(prob, 20);
        g->barabasiAlbert(qtNodes);
        g->printAdjMatrix();
        std::cout << std::endl << std::endl;
        g->initializeDistMatrix();
        g->floydWarshall();
        g->printDistMatrix();
    }

    std::cout << std::endl;
    std::cout << "Mean: " << g->calculateMean() << std::endl;
    std::cout << "Longest Path: " << g->findLongestPath() << std::endl;

    std::ofstream outfile("output.txt");
    outfile << g->calculateMean() << " " << g->findLongestPath() << std::endl;
    outfile.close();

    delete g;
}
