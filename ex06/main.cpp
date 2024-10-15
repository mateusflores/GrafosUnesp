#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

int main() {
    int qtNodes = 4;    

    // Inicializar o grafo com base no arquivo
    std::ifstream f("exemplo.dat");
    Graph *g = new Graph(f);

    // Inicializa a Matriz de Adjacencias
    g->initializeAdjMatrix(qtNodes);
    // Gera a Matriz de Adjacencias
    g->generateAdjMatrix();
    // Printa a Matriz de Adj para verificar se está tudo nos conformes
    g->printAdjMatrix();
    // Gera uma lista de vertices que fazem parte da clique maximal
    int nodeInicial = 0;
    std::vector<int> listCliqueMaximal = g->cliqueMaximal(nodeInicial);

    // Printa a lista de vertices que fazem parte da clique maximal
    for(int i = 0; i < listCliqueMaximal.size(); i++){
        std::cout << listCliqueMaximal[i] << " ";
    }
    
    std::cout << std::endl;

    delete g;
}
