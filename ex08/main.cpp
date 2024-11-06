#include <iostream>
#include <fstream>
#include "Graph.h"

int main() {
    int qtNodes = 5;
    // Inicializar o grafo com base no arquivo
    std::ifstream f("exemplo.dat");
    Graph *g = new Graph(f, qtNodes);

    std::cout << "Executando o algoritmo de Hierholzer..." << std::endl;
    std::vector<int> eulerianCircuit = g->hierholzer();

    if (eulerianCircuit.empty()) {
        std::cout << "Não foi possível encontrar um circuito euleriano." << std::endl;
    } else {
        std::cout << "Circuito Euleriano encontrado: ";
        for (int v : eulerianCircuit) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;

    delete g;
}
