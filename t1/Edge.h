#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Edge {
private:
    Node* source;
    Node* destination;
    int weight;

public:
    Edge(Node* source, Node* destination, int weight = 1.0);

    Node* getSource() const;
    Node* getDestination() const;
    int getWeight() const;

    void setWeight(int newWeight);
};

#endif  // EDGE_H
