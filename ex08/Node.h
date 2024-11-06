#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <set>
#include "Edge.h"

class Edge;

class Node {
private:
    
    int id;                     // O id do Node
    std::set<int> neighbors;    // vizinhos
    std::set<Edge> edges;       // Um set de arestas (obs.: Edge != Edge*)

public:
    // Construtor da classe Node
    Node(int id);
    
    // Retorna o ID do Node
    int getId() const;
    
    // Retorna as arestas que se ligam ao Node
    std::set<Edge> getEdges() const;

    // Adiciona uma aresta ligada ao Node
    void addEdge(Edge* edge);

    // Remove uma aresta ligada ao Node
    void removeEdge(Edge* edge);

    // Verifica se existe uma determinada aresta ligada ao Node
    bool hasEdge(const Edge* edge) const;

    // adiciona vizinho na lista de vizinhos
    void addNeighbor(int neighborID);

    std::set<int> getNeighbors();
};

#endif  // NODE_H
