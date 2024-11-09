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
    
    vector<set<int>> adj;
    int N; 
    int K;
    double p;

public:

    void addNode();
    
    void addEdge(int i, int j);

    void erdosRenyi(double prob, int qtNodes);

    void initializeAdjVector(int qtNodes);

    void displayAdjList();

    void wattsStrogatzGraph (int vertices, int neighbors, double prob);

    void generateRegularGraph();

    void rewireEdges();

};

#endif  // GRAPH_H