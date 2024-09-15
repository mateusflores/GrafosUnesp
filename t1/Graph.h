#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

class Graph {
private:
    std::unordered_map<int, Node*> nodes;  // Store nodes by their IDs
    std::vector<Edge*> edges;              // Store all edges in the graph

public:
    // Constructor and Destructor
    Graph();
    Graph(std::ifstream &f);
    ~Graph();

    // Node management
    Node* addNode(int id);
    void removeNode(int id);
    Node* getNode(int id) const;

    // Edge management
    Edge* addEdge(int sourceId, int destinationId, int weight = 1.0);
    void removeEdge(int sourceId, int destinationId);
    std::vector<Edge*> getEdges() const;
    Edge* getEdge(int sourceId, int destinationId) const;

    // Graph utility
    bool nodeExists(int id) const;
    bool edgeExists(int sourceId, int destinationId) const;
    void printAdjMatrix();
};

#endif  // GRAPH_H