#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Graph {
private:
    int qtNodes;
    vector<set<int>> adj;
    int K;

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

    void wattsStrogatz(int neighbors, double prob);

    void generateRegularGraph();

    void rewireEdges(double p);
};

#endif  // GRAPH_H