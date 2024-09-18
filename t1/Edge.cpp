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

bool Edge::operator==(const Edge& other) const {
    return (source->getId() == other.getSource()->getId() && destination->getId() == other.getDestination()->getId()) || 
    (source->getId() == other.getDestination()->getId() && destination->getId() == other.getSource()->getId());
}

bool Edge::operator<(const Edge& other) const {
    if (source->getId() != other.getSource()->getId()) {
        return source->getId() < other.getSource()->getId();
    }

    return destination->getId() < other.getDestination()->getId();
}