#include "Edge.h"


Edge::Edge(Node* source, Node* destination, int weight)
    : source(source), destination(destination), weight(weight) {}

Node* Edge::getSource() const {
    return source;
}

Node* Edge::getDestination() const {
    return destination;
}

int Edge::getWeight() const {
    return weight;
}

void Edge::setWeight(int newWeight) {
    weight = newWeight;
}
