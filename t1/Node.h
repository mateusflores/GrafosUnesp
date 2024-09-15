#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Edge;

class Node {
private:
    int id;
    std::vector<Edge*> edges;

public:
    Node(int id);
    
    int getId() const;
    std::vector<Edge*> getEdges() const;

    void addEdge(Edge* edge);
    void removeEdge(Edge* edge);

    bool hasEdge(const Edge* edge) const;
};

#endif  // NODE_H
