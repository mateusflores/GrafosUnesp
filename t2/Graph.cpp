#include "Graph.h"
#include <random>

double getRandomProb(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distr(0.0, 1.0);

    return distr(gen);
}

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

void Graph::wattsStrogatzGraph (int vertices, int neighbors, double prob) {
    N = vertices;
    K = neighbors;
    p = prob;
    adj = std::vector<std::set<int>>(vertices);
}

void Graph::generateRegularGraph() {
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= K / 2; j++) {
            int neighbor = (i + j) % N;
            adj[i].insert(neighbor);
            adj[neighbor].insert(i);
        }
    }
}

void Graph::rewireEdges() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> nodeDist(0, N - 1);

    for (int i = 0; i < N; i++) {
        std::vector<int> rightNeighbors;
        for (int j = 1; j <= K / 2; j++) {
            int neighbor = (i + j) % N;
            rightNeighbors.push_back(neighbor);
        }

        for (int neighbor : rightNeighbors) {
            if (getRandomProb() < p) {
                int newNeighbor;
                do {
                    newNeighbor = nodeDist(gen);
                } while (newNeighbor == i || adj[i].count(newNeighbor));

                adj[i].erase(neighbor);
                adj[neighbor].erase(i);
                adj[i].insert(newNeighbor);
                adj[newNeighbor].insert(i);
            }
        }
    }
}


