#include "Graph.h"
#include <random>

double getRandomProb(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distr(0.0, 1.0);

    return distr(gen);
}

void Graph::addNode() {
    adj.push_back(vector<int>());
}

void Graph::addEdge(int i, int j) {
    adj[i].push_back(j);
    adj[j].push_back(i);
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


