#include "Graph.h"

using namespace std;

void printArgs(double prob, int qtNodes, string graphType, int qtNeighbors){
    cout << "Probabilidade: " << prob << endl;
    cout << "Quantidade de nós: " << qtNodes << endl;
    cout << "Tipo de Grafo: " << graphType << endl;
    if(qtNeighbors)
        cout << "Quantidade vizinhos(K): " << qtNeighbors << endl;
    cout << endl;
}

/* COMO INVOCAR MAIN 
*   ./main prob qtNodes graphType
*   ./main 0.5 50 er
*
*   ./main prob qtNodes graphType qtNeihbors
*   ./main 0.5 50 ws 7
*/

int main(int argc, char *argv[]) {
    string graphType;
    double prob;
    int qtNodes = 0, qtNeighbors = 0;

    prob = stod(argv[1]); 
    qtNodes = stoi(argv[2]);
    graphType = argv[3];

    if(argc == 5){
        qtNeighbors = stoi(argv[4]);
    }

    printArgs(prob, qtNodes, graphType, qtNeighbors);
    
    Graph *g = new Graph(qtNodes);

    // Erdos-Renyi
    if(graphType == "er"){
        g->initializeAdjVector(qtNodes);
        g->erdosRenyi(prob, qtNodes);
        cout << "Lista de adjacencias:" << endl;
        g->displayAdjList();
    }
    // Watts-Strogatz
    else if (graphType == "ws"){
        g->initializeAdjVector(qtNodes);
        g->wattsStrogatz(qtNeighbors, prob);
        cout << "Lista de adjacencias:" << endl;
        g->displayAdjList();
    }

    /* GERAÇÃO DOS RESULTADOS
    *   FORMATO: LIMITE_INFERIOR_CROMATICO LIMITE_SUPERIOR_CROMATICO 
    *
    *   Joga os resultados para o um arquivo chamado output.txt
    *
    */

    std::ofstream outfile("output.txt");
    outfile << g->findLowerBoundChromaticNumber(10) << " " << g->findUpperBoundChromaticNumber() << std::endl;
    outfile.close();

    delete g;

    return 0;
}