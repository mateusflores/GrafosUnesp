#include "Graph.h"
#include <random>
#include <algorithm>

double getRandomProb(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distr(0.0, 1.0);

    return distr(gen);
}

int generateRandomInt(int upperBound) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, upperBound - 1);

    return distr(gen);
}

Graph::Graph(int qtNodes) : qtNodes(qtNodes) {};

void Graph::addNode() {
    adj.push_back(set<int>());
}

void Graph::addEdge(int i, int j) {
    adj[i].insert(j);
    adj[j].insert(i);
}

void Graph::displayAdjList() {
    for (int i = 0; i < adj.size(); i++) {
        cout << i << ": ";
        for (int j : adj[i]) {
            cout << j << " ";
        }
        cout << endl; 
    }
}

void Graph::initializeAdjVector(int qtNodes){
    for(int i = 0; i < qtNodes; i++){
        addNode();    
    }
}

void Graph::erdosRenyi(double prob, int qtNodes){
    for (int i = 0; i < qtNodes; i++){
        for (int j = i + 1; j < qtNodes; j++){
            if (getRandomProb() < prob){

                addEdge(i, j);
            }
        }
    }
}

bool Graph::isNeighborOfEveryItem(int u) {
    if (adj[u].size() == qtNodes - 1)
        return true;
    return false;
}

// Algoritmo CliqueMaximal
vector<int> Graph::findMaxClique(int v) {
    // Lista para armazenar a clique maximal
    vector<int> maxClique;
    // Insere o vértice 'v' em 'maxClique' - vertice inicial
    maxClique.push_back(v);
    // Contador para verificar se ainda há vértices para adicionar
    int c = 1;
    
    while (c > 0) {
        // Restart contador
        c = 0;
        
        // Itera sobre todos os vértices do grafo
        for (int u = 0; u < qtNodes; u++) {
            // Se u ainda ñ está em maxClique e é vizinho de todos os itens de maxClique
            if (find(maxClique.begin(), maxClique.end(), u) == maxClique.end() && isNeighborOfEveryItem(u)) {
                // Adiciona 'u' à lista de vértices da clique
                maxClique.push_back(u); 
                c++; // Incrementa o contador
            }
        }
    }
    
    // Retorna a lista de vertices que compoem a clique maximal
    return maxClique;
}

int Graph::getMaxDegree(){
    int maxDegree = 0;
    for (int i = 0; i < qtNodes; i++)
        if (adj[i].size() > maxDegree)
            maxDegree = adj[i].size();  
    return maxDegree;
}

int Graph::findUpperBoundChromaticNumber(){
    return getMaxDegree();
}

int Graph::findLowerBoundChromaticNumber(int qtAttempts){
    int largestCliqueSize = 0;
    int randomNode = 0;
    int temp = 0;

    for(int i = 0; i < qtAttempts; i++){
        randomNode = generateRandomInt(qtNodes);
        temp = findMaxClique(randomNode).size();
        if (temp > largestCliqueSize)
            largestCliqueSize = temp;
    }

    return largestCliqueSize;
}

void Graph::wattsStrogatz(int neighbors, double prob) {
    K = neighbors;

    generateRegularGraph();
    displayAdjList();
    rewireEdges(prob);
}

void Graph::generateRegularGraph() {
    for (int i = 0; i < qtNodes; i++) {
        for (int j = 1; j <= K / 2; j++) {
            int neighbor = (i + j) % qtNodes;
            adj[i].insert(neighbor);
            adj[neighbor].insert(i);
        }
    };  
}

void Graph::rewireEdges(double p) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> probDist(0.0, 1.0);
    uniform_int_distribution<> nodeDist(0, qtNodes - 1);

    for (int i = 0; i < qtNodes; i++) {
        vector<int> rightNeighbors;
        for (int j = 1; j <= K / 2; j++) {
            int neighbor = (i + j) % qtNodes;
            rightNeighbors.push_back(neighbor);
        }

        for (int neighbor : rightNeighbors) {
            double bla = probDist(gen);
            cout << "bla: " << bla << endl;
            if (bla < p) {
                int newNeighbor;
                do {
                    newNeighbor = nodeDist(gen);
                    cout << "bla2: " << newNeighbor << endl;
                } while (newNeighbor == i || adj[i].count(newNeighbor));

                adj[i].erase(neighbor);
                adj[neighbor].erase(i);
                adj[i].insert(newNeighbor);
                adj[newNeighbor].insert(i);
            }
        }
    }
}