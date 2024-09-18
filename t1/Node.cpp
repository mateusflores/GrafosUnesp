#include "Node.h"

// Constructor
Node::Node(int id) : id(id) {}

// Get ID
int Node::getId() const {
    return id;
}

// Get edges (returns the set of edges)
std::set<Edge> Node::getEdges() const {
    return edges;
}

// Add edge by dereferencing Edge pointer
void Node::addEdge(Edge* edge) {
    edges.insert(*edge);  // Dereference edge pointer and insert Edge object into the set
}

// Remove edge by dereferencing Edge pointer
void Node::removeEdge(Edge* edge) {
    edges.erase(*edge);  // Dereference and remove Edge object from the set
}

// Check if the edge exists in the set by dereferencing
bool Node::hasEdge(const Edge* edge) const {
    return edges.find(*edge) != edges.end();  // Dereference and find the Edge in the set
}
