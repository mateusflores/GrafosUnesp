#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Graph {
private:
    
    vector<vector<int>> adj;

public:

    void addNode();
    
    void addEdge(int i, int j);

    void erdosRenyi(double prob, int qtNodes);

    void initializeAdjVector(int qtNodes);

    void displayAdjList();

};

#endif  // GRAPH_H