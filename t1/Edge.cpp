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
    // Compara (src == other.src and dest == other.dest) or (src == other.dest and dest == other.src)
    // de modo que aresta(u, v) == aresta(v, u) seja TRUE
    return (source->getId() == other.getSource()->getId() && destination->getId() == other.getDestination()->getId()) || 
    (source->getId() == other.getDestination()->getId() && destination->getId() == other.getSource()->getId());
}

bool Edge::operator<(const Edge& other) const {
    // Comparação necessária para o uso do std::set, mas de fato pouco útil pois compara apenas os ids
    // Se o primeiro valor for menor, então this é menor que other
    // Se o primeiro valor for igual, então o valor lógico depende da comparação do id do segundo valor.
    if (source->getId() != other.getSource()->getId()) {
        return source->getId() < other.getSource()->getId();
    }

    return destination->getId() < other.getDestination()->getId();
}