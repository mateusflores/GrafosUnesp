#include "Node.h"
#include "Edge.h"
#include <algorithm>

// Constructor
Node::Node(int id) : id(id) {}

// Getters
int Node::getId() const {
    return id;
}

std::vector<Edge*> Node::getEdges() const {
    return edges;
}


// Edge management
void Node::addEdge(Edge* edge) {
    edges.push_back(edge);
}

void Node::removeEdge(Edge* edge) {
    edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
}

bool Node::hasEdge(const Edge* edge) const {
    return std::find(edges.begin(), edges.end(), edge) != edges.end();
}
