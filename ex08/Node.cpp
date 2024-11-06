#include "Node.h"

Node::Node(int id) : id(id) {}

int Node::getId() const {
    return id;
}

std::set<Edge> Node::getEdges() const {
    return edges;
}

void Node::addEdge(Edge* edge) {
    // Note que a inserção é feita dereferenciando o pointer, visto que para
    // que o std::set consiga fazer comparações, deve fazer com a classe em si
    // e não sobre os pointers. Caso contrário, ele compararia valores de endereço.
    edges.insert(*edge);
}

void Node::removeEdge(Edge* edge) {
    // Note que a remoção é feita dereferenciando o pointer, visto que para
    // que o std::set consiga fazer comparações, deve fazer com a classe em si
    // e não sobre os pointers. Caso contrário, ele compararia valores de endereço.
    edges.erase(*edge);
}

bool Node::hasEdge(const Edge* edge) const {
    return edges.find(*edge) != edges.end();
}

void Node::addNeighbor(int neighborID){
    neighbors.insert(neighborID);
}

std::set<int> Node::getNeighbors(){
    return neighbors;
}
