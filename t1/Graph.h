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
    std::vector<std::vector<int>> adjMatrix;
    std::vector<std::vector<int>> distMatrix;

public:
    // Constructor and Destructor
    Graph();
    Graph(std::ifstream &f);
    ~Graph();

    // relacionadas a vertices
    Node* addNode(int id);
    void removeNode(int id);
    Node* getNode(int id) const;

    // relacionadas a arestas
    Edge* addEdge(int sourceId, int destinationId, int weight = 1.0);
    void removeEdge(int sourceId, int destinationId);
    std::vector<Edge*> getEdges() const;
    Edge* getEdge(int sourceId, int destinationId) const;

    // relacionadas a matriz de adjacencias
    void generateAdjMatrix();
    std::vector<std::vector<int>> getAdjMatrix() const;

    // Graph utility
    bool nodeExists(int id) const;
    bool edgeExists(int sourceId, int destinationId) const;
    void printAdjMatrix();

    void initializeDistMatrix();
    void floydWarshall();
    void printDistMatrix();
};

#endif  // GRAPH_H