#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Graph {
private:
    int qtNodes;
    vector<vector<int>> adj;

public:
    Graph(int qtNodes);

    void addNode();
    
    void addEdge(int i, int j);

    void erdosRenyi(double prob, int qtNodes);

    void initializeAdjVector(int qtNodes);

    void displayAdjList();

    bool isNeighborOfEveryItem(int u);

    vector<int> findMaxClique(int v);
    
    int getMaxDegree();

    int findUpperBoundChromaticNumber();

    int findLowerBoundChromaticNumber(int qtAttempts);
};

#endif  // GRAPH_H