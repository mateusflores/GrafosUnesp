#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Node;

class Edge {
private:
    Node* source;
    Node* destination;
    int weight;

public:
    Edge(Node* source, Node* destination, int weight = 1);

    Node* getSource() const;
    Node* getDestination() const;
    int getWeight() const;

    void setWeight(int newWeight);

    bool operator==(const Edge& other) const;
    bool operator<(const Edge& other) const;
};

#endif  // EDGE_H
