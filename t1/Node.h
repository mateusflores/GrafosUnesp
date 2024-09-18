#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <set>
#include "Edge.h"

class Edge;

class Node {
private:
    int id;
    std::set<Edge> edges;

public:
    Node(int id);
    
    int getId() const;
    std::set<Edge> getEdges() const;

    void addEdge(Edge* edge);
    void removeEdge(Edge* edge);

    bool hasEdge(const Edge* edge) const;
};

#endif  // NODE_H
